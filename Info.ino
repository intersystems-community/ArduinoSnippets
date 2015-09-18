/*
 * A simple programme that will record humidity, temperature and brightness
 *  temperature and brightness and send them to COM port
 * Output format: H=1.0;T=1.0;LL=1;
 * 
 */

//PhotoResistor Pin
int lightPin = 0; //the analog pin the photoresistor is 
                  //connected to
                  //the photoresistor is not calibrated to any units so
                  //this is simply a raw sensor value (relative light)


// DHT-11 Brick pin 
int DHpin = 8; 

byte dat[5]; 

//LED Pin
int ledPin = 13;  //the pin the LED is connected to
                  //we are controlling brightness so 
                  //we use one of the PWM (pulse width
                  // modulation pins)
				  
byte read_data() 
{ 
    byte data; 
  for(int i=0; i<8; i++) 
  { 
    if(digitalRead(DHpin) == LOW) 
    { 
      while(digitalRead(DHpin) == LOW);     
      delayMicroseconds(30);    
      if(digitalRead(DHpin) == HIGH) 
      data |= (1<<(7-i));                                                                                                                                                                   
 
            while(digitalRead(DHpin) == HIGH); 
    }   
  } 
        return data; 
} 

// Get data from DHT-11 Brick sensor
void start_test() 
{ 
  digitalWrite(DHpin,LOW);  
  delay(30);  
  digitalWrite(DHpin,HIGH); 
  delayMicroseconds(40);  
                pinMode(DHpin,INPUT); 
                while(digitalRead(DHpin) == HIGH); 
                delayMicroseconds(80);     
                if(digitalRead(DHpin) == LOW); 
                delayMicroseconds(80);    
                for(int i=0;i<4;i++)      
                dat[i] = read_data(); 
              pinMode(DHpin,OUTPUT);                                                                                                                                                             
              digitalWrite(DHpin,HIGH);    
} 


// Initial setup
void setup()
{
   Serial.begin(9600); 
   pinMode(DHpin,OUTPUT); 
}
 /*
 * loop() - this function will start after setup 
 * finishes and then repeat
 */
void loop()
{
    delay(1000); 
    int lightLevel = analogRead(lightPin); //Read the lightlevel
         
    start_test(); 
    Serial.print("H="); 
    Serial.print(dat[0], DEC);   
    Serial.print('.'); 
    Serial.print(dat[1],DEC);    
    Serial.print(";T="); 
    Serial.print(dat[2], DEC);    
    Serial.print('.'); 
    Serial.print(dat[3],DEC);     
    Serial.print(";LL="); 
    Serial.print(lightLevel);
    Serial.println(";");
}
