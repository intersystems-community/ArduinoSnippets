
/******************************************
        PURPOSE:  Learn to use the MF522-AN RFID card reader
  Created by      Rudy Schlaf for www.makecourse.com
  DATE:   2/2014
*******************************************/

/*
 * This sketch uses the MFRC522 Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 *
 * This library has been released into the public domain.
*/


#include <SPI.h>//include the SPI bus library
#include <MFRC522.h>//include the RFID reader library

#define SS_PIN 10  //slave select pin
#define RST_PIN 9  //reset pin

#define u1b 2  //Block on a card for user1 byte array
#define u2b 4 
#define p1b 5 
#define p2b 6 

MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information

int block = 2; //this is the block number we will write into and then read. Do not write into 'sector trailer' block, since this can make the block unusable.

byte blockcontent[16] = {"ma2ecohrse_____"};//an array with 16 bytes to be written into one of the 64 card blocks is defined
byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.

String inString = ""; // COM port incoming data buffer

void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  Serial.println("Scan a MIFARE Classic card");

  // Prepare the security key for the read and write functions - all six key bytes are set to 0xFF at chip delivery from the factory.
  // Since the cards in the kit are new and the keys were never defined, they are 0xFF
  // if we had a card that was programmed by someone else, we would need to know the key to be able to access it. This key would then need to be stored in 'key' instead.

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  // Receive data from com port
  while (Serial.available() > 0) {
    int inChar = Serial.read();

    if (inChar != '\n') {
      inString += (char)inChar;
    } else {
      // New line
      while (!initcard());
      
      String Action = inString.substring(0, 3);
      if (Action == "Set") {
        SetUserAndPassToCard(inString);
      } else if (Action == "Get") {
        ReadUserAndPassToCom();
      } else {
        Serial.println(Action);
      }
      
      disconnectCard();
      inString = "";
    }
  }
}

void ReadUserAndPassToCom()
{
  readBlockToCom(u1b);
  readBlockToCom(u2b);
  Serial.write("@");
  readBlockToCom(p1b);
  readBlockToCom(p2b);
  Serial.println("");
}

void SetUserAndPassToCard(String Data) {
  Serial.println(Data);
  // Data Set@user1@user2@pass1@pass2
  // Set@1234567890123456@1234567890123456@1234567890123456@1234567890123456
  byte user1[16], user2[16], pass1[16], pass2[16];

  String user1str = inString.substring(4, 20);
  String user2str = inString.substring(21, 37);
  String pass1str = inString.substring(38, 54);
  String pass2str = inString.substring(55, 71);

  Serial.println("Arrays");

  stringToArray(user1str, user1, sizeof(user1));
  stringToArray(user2str, user2, sizeof(user2));
  stringToArray(pass1str, pass1, sizeof(pass1));
  stringToArray(pass2str, pass2, sizeof(pass2));

  /*writeByteArray(user1, 16);
  writeByteArray(user2, 16);
  writeByteArray(pass1, 16);
  writeByteArray(pass2, 16);*/


  writeBlock(u1b, user1); //the blockcontent array is written into the card block
  writeBlock(u2b, user2);
  writeBlock(p1b, pass1);
  writeBlock(p2b, pass2);
  //readBlockToCom(2);

}

void stringToArray(String str, byte array[], int arrlength)
{
  for (int j = 0 ; j < arrlength ; j++)
  {
    array[j] =  str.charAt(j);
  }
}

void writeByteArray(byte array[], int arrlength)
{
  for (int j = 0 ; j < arrlength ; j++) //print the block contents
  {
    Serial.write (array[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
  }
  Serial.println("");
}



bool initcard()
{
  // Look for new cards (in case you wonder what PICC means: proximity integrated circuit card)
  if ( ! mfrc522.PICC_IsNewCardPresent()) {//if PICC_IsNewCardPresent returns 1, a new card has been found and we continue
    return false; //if it did not find a new card is returns a '0' and we return to the start of the loop
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
    return false; //if it returns a '0' something went wrong and we return to the start of the loop
  }
  return true;
}

void disconnectCard()
{
  // Halt PICC
  mfrc522.PICC_HaltA();
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
}



void readBlockToCom(int number)
{
  readBlock(number, readbackblock);//read the block back
  for (int j = 0 ; j < 16 ; j++) //print the block contents
  {
    Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
  }
}



