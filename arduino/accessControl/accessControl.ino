/*
 * This program is modeified from an example provided by the RC522 library:
 * https://github.com/miguelbalboa/rfid
 * 
 * Author: BoolLi
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>
#include <math.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_1_PIN        22          // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2
#define SS_2_PIN        23          // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 1

#define NR_OF_READERS   2

byte ssPins[] = {SS_1_PIN, SS_2_PIN};

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  
  SPI.begin();                // Init SPI bus
  
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

/**
 * Main loop.
 */
/*void loop() {

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);
      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.println();
      Serial.print(F("PICC type: "));
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}*/

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
/*void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}*/

void loop() {
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
      
      // Look for new cards
      if ( !mfrc522[reader].PICC_IsNewCardPresent()) {
              return;
      }
  
      // Select one of the cards
      if ( !mfrc522[reader].PICC_ReadCardSerial())    return;
      unsigned long int id = 0;
  
      Serial.print("Card UID:");    //Dump UID
      for (byte i = 0; i < mfrc522[reader].uid.size; i++) {
        Serial.print(mfrc522[reader].uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522[reader].uid.uidByte[i], HEX);
        id += mfrc522[reader].uid.uidByte[i] * (long) pow(256, i);
      }
  
      Serial.print(" ISIC ID: ");
      Serial.print(id);
  
      Serial.print(" PICC type: ");   // Dump PICC type
      byte piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));
      mfrc522[reader].PICC_HaltA(); // Halt PICC
    }
}

