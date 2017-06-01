/*
Typical pin layout used:
--------------------------------
MFRC522      Arduino
Reader/PCD   Mega
Signal      Pin          Pin
--------------------------------
RST/Reset   RST          Custom
SPI SS 1    SDA(SS)      Custom
SPI MOSI    MOSI         51
SPI MISO    MISO         50
SPI SCK     SCK          52
*/

//=========//
// DEFINES //
//=========//
#define MAX_RETRY 3         // Max retry count

#define RFID_RST_PIN 9      // RFID Reset PIN
#define RFID_SS_PIN 11      // RFID SlaveSelect PIN

#define LED_BLUE_PIN 3      // Blue LED PIN
#define LED_YELLOW_PIN 5    // Yellow LED PIN
#define LED_RED_PIN 13      // Red LED PIN

#define RESET_PIN 6         // Board Reset PIN
#define RELAY_PIN 2

//==========//
// INCLUDES //
//==========//
#include <Arduino.h>
#include <EEPROM.h>
#include <SPI.h>
#include <avr/pgmspace.h>

#include <MFRC522.h>
#include <Ethernet2.h>
#include <ArduinoJson.h>

//=========//
// Structs //
//=========//
struct SimpleResponse {
    char status;
};

//==================//
// GLOBAL VARIABLES //
//==================//
bool led_Enabled = false;       // LED init status
bool relay_Enabled = false;     // Relay init status
bool eth_Enabled = false;       // Ethernet init status

bool relayStatus = false;       // Relay status
bool readStatus = false;        // Successful card read

byte readCard[4];   // Last read card
char cReadCard[16]; // Last read card HEX

byte ethMac[] = {0x86, 0xF3, 0xB0, 0x7A, 0x6B, 0x4C};   // Mac address
char apiServer[] = "192.168.10.2";                      // API server address Ex: 192.168.10.2 or id.kuristiku.ee. Make sure to change port below
int apiServerPort = 80;                               // API server port
long apiTimeout = 10000;                                // API server Timeout

long controllerToken = -1;  // Controller token
long previousMillis = 0;        // will store last time LED was updated
long interval = 10000; // When to close door

//=========//
// OBJECTS //
//=========//
MFRC522 RFID(RFID_SS_PIN, RFID_RST_PIN);    // RFID
EthernetClient ethClient;                   // Ethernet

//=======//
// SETUP //
//=======//
#define debug_setup
void setup() {
    // Init LED PINS
    init_LED();

    // Loading Status
    LED_Status(2);

    #if defined(debug_setup)
    // Init serial communications with the PC
    Serial.begin(9600);
    #endif

    #if defined(debug_setup)

    Serial.println();
    Serial.println(F("==========Starting=========="));
    #endif

    #if defined(debug_setup)
    // Init SPI bus
    Serial.print(F("Init SPI..."));
    SPI.begin();
    Serial.println(F(" [OK]"));
    #else
    SPI.begin();
    #endif

    // Init Reset
    init_RESET();

    // Init Relay
    init_RELAY();

    // Init Random number generator
    randomSeed(analogRead(0));

    // Init Ethernet
    init_Ethernet();

    // Init Controller registration
    init_Register();

    // Init RFID readers
    init_RFID();

    // Ready!
    LED_Status(1);

    #if defined(debug_setup)
    Serial.println(F("============DONE============"));
    #endif
}

//======//
// LOOP //
//======//
void loop() {
    delay(5);

    Relay_Timer();

    // Check for new cards
    readStatus = GetID();

    if (readStatus) {
        // We found a new card
        LED_Status(2);

        // Log the entry
        AccessLog();

        // Check for access
        relayStatus = CheckPermission();

        previousMillis = millis();

        if (relayStatus) {
            Serial.println(F("Access Granted"));
            LED_Status(1);
            digitalWrite(RELAY_PIN, relayStatus);
        } else {
            Serial.println(F("Access Denied"));
            LED_Status(3);
        }
    }
}
