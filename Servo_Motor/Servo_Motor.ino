-----------------------------------------------------------------
//---Header files and import of other important files for RFID---
-----------------------------------------------------------------

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[3];

-----------------------------------------------------------------
//---Header files and import of other important files for Servo--
-----------------------------------------------------------------

// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 3; 
// Create a servo object 
char x;
Servo Servo1;

-----------------------------------------------------------------
-----------------------------------------------------------------


void setup() { 

     Serial.begin(9600);//common for both

  -----------------------------------------------------------
  //---------------------Setup for Servo---------------------
  -----------------------------------------------------------
  
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 


   -----------------------------------------------------------
  //---------------------Setup for RFID-----------------------
   -----------------------------------------------------------
   
   SPI.begin(); // Init SPI bus
   rfid.PCD_Init(); // Init MFRC522 
   
   for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
   }

   -----------------------------------------------------------
   -----------------------------------------------------------
   
   
   
}



int b=1;


void loop(){
  
  if(b==1){
    Servo1.write(0); 
   delay(500); 
   b=0;
  }

  x= Serial.read();
  
  if(x=='1'){
    Serial.println("Animal Captured!!!");
    Servo1.write(90);
    delay(500);
  }
  
}

//void loop(){ 
//   // Make servo go to 0 degrees 
//   Servo1.write(0); 
//   delay(1000); 
//
//   // Make servo go to 180 degrees 
//   Servo1.write(180); 
//   delay(1000); 
//}
