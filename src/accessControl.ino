/*
   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required *
   SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required *
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <math.h>

// RFID
#include <MFRC522.h>

// MYSQL
#include "MySQL_Connection.h"
#include "MySQL_Cursor.h"
#include "MySQL_Encrypt_Sha1.h"
#include "MySQL_Packet.h"

// Ethernet
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

// ETHERNET
byte mac_addr[] = { 0xAD, 0x0L, 0xF0, 0x42, 0x00, 0x69 };
EthernetClient client;

// MYSQL
IPAddress server_addr(192,168,10,2);  // IP of the MySQL *server* here
char user[] = "kuristiku";              // MySQL user login username
char password[] = "eFo04ppjNkG3JJOD";        // MySQL user login password

MySQL_Connection conn((Client *)&client);

// RFID
#define RST_PIN         3
#define SS_1_PIN        40
#define SS_2_PIN        41

#define NR_OF_READERS   2

byte ssPins[] = {SS_1_PIN, SS_2_PIN};

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

void setup() {
  // Initialize serial communications with the PC
  Serial.begin(9600);

  // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  while (!Serial);

  // Init Ethernet
  Ethernet.begin(mac_addr);

  Serial.println("MYSQL | Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
  }
  else
    Serial.println("MYSQL | Connection failed.");

  // Init SPI bus
  SPI.begin();

  // Init each MFRC522 card
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

/**
   Main loop.
*/
/*
void loop() {
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {

    // Look for new cards
    if (!mfrc522[reader].PICC_IsNewCardPresent()) {
      return;
    }

    // Select one of the cards
    if (!mfrc522[reader].PICC_ReadCardSerial()) {
      return;
    }

    unsigned long int id = 0;

    //Dump UID
    Serial.print("Card UID:");
    for (byte i = 0; i < mfrc522[reader].uid.size; i++) {
      Serial.print(mfrc522[reader].uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522[reader].uid.uidByte[i], HEX);
      id += mfrc522[reader].uid.uidByte[i] * (long) pow(256, i);
    }

    Serial.print(" ISIC ID: ");
    Serial.print(id);

    // Dump PICC type
    Serial.print(" PICC type: ");
    byte piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
    Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));

    // Halt PICC
    mfrc522[reader].PICC_HaltA();
  }
}
*/

/**
 * Main loop.
 */
void loop() {

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
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
