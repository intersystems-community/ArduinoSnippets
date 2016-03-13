
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

void loop()
{
  // Receive data from com port
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // Получаем 1 символ,
      // Прибавляем его к строке
      inString += (char)inChar;
    }

    // Доходим до новой строки
    if (inChar == '\n') {
      //Serial.println(inString);
      // inString = "Action@Arg1:Arg2..."
      String Action = inString.substring(1,3);
      Serial.println(Action);
      //byte Action[3],Args[1];
      //String Arguments = "";
      //int n = sscanf(inString.c_str(), "%s@%s", Action,Args);
      if (Action =="Set") {
        Serial.println("0");
      } else if (Action =="Get") {
        Serial.println("1");
      } else {
        Serial.println(Action);
      }
      inString = "";
    }
    /*while (!initcard());


    writeBlock(block, blockcontent);//the blockcontent array is written into the card block
    readBlockToCom(2);*/
  }
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



void readBlockToCom(int number)
{
  readBlock(number, readbackblock);//read the block back
  Serial.print("read block: ");
  for (int j = 0 ; j < 16 ; j++) //print the block contents
  {
    Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
  }
  Serial.println("");
}



