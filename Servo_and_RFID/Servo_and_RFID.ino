//-----------------------------------------------------------------
//---Header files and import of other important files for RFID---
//-----------------------------------------------------------------

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[3];

//-----------------------------------------------------------------
//---Header files and import of other important files for Servo--
//-----------------------------------------------------------------

// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 3; 
// Create a servo object 
char x;
Servo Servo1;

//-----------------------------------------------------------------
//-----------------------------------------------------------------


void setup() { 

   Serial.begin(9600);//common for both

  //-----------------------------------------------------------
  //---------------------Setup for Servo---------------------
  //-----------------------------------------------------------
  
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 


   //-----------------------------------------------------------
  //---------------------Setup for RFID-----------------------
   //-----------------------------------------------------------
   
   SPI.begin(); // Init SPI bus
   rfid.PCD_Init(); // Init MFRC522 
   
   for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
   }

   //-----------------------------------------------------------
   //-----------------------------------------------------------
   
   
   
}



int b=1;


void loop(){

  //-----------------------------------------------------------
  //---------------------Loop for Servo----------------------
  //-----------------------------------------------------------
  
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



  //-----------------------------------------------------------
  //---------------------Loop for RFID-----------------------
  //-----------------------------------------------------------

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  
  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   

    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();


  //-----------------------------------------------------------
  //------------------------------------------------------------
  
}


//-----------------------------------------------------------
//----------Other necessary items for RFID-----------------
//-----------------------------------------------------------

/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
