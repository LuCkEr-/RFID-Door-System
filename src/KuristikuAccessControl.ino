/*
   Typical pin layout used:
   --------------------------------
               MFRC522      Arduino
               Reader/PCD   Mega
   Signal      Pin          Pin
   --------------------------------
   RST/Reset   RST          Custom
   SPI SS 1    SDA(SS)      Custom
   SPI SS 2    SDA(SS)      Custom
   SPI MOSI    MOSI         51
   SPI MISO    MISO         50
   SPI SCK     SCK          52
*/

//==========//
// INCLUDES //
//==========//
  //------//
  // RFID //
  //------//
  #include <MFRC522.h>
  #include <SPI.h>

//=========//
// DEFINES //
//=========//
  //------//
  // RFID //
  //------//
  // RST/Reset | PIN
  #define RST_PIN       3

  // SDA       | PIN
  #define SDA_PIN_1     40
  #define SDA_PIN_2     41

  // Number of readers
  #define READER_TOTAL  1

  //-----//
  // LED //
  //-----//
  #define LED_RED_PIN 9
  #define LED_GREEN_PIN 10
  #define LED_BLUE_PIN 11

//===========//
// INSTANCES //
//===========//
  //------//
  // RFID //
  //------//
  // MFRC522 instance.
  MFRC522 mfrc522[READER_TOTAL];


//==================//
// GLOBAL VARIABLES //
//==================//
  //------//
  // RFID //
  //------//
  byte sdaPins[] = {SDA_PIN_1, SDA_PIN_2};

  //----------------//
  // TESTING VALUES //
  //----------------//
  const int TotalLoadedCards = 10;

//=======//
// SETUP //
//=======//
void setup() {
  // Init serial communications with the PC
  Serial.begin(9600);

  // Wait while the serial port is being opened
  while (!Serial);
  Serial.println();
  Serial.println("Starting...");

  // Init SPI bus
  SPI.begin();

  // Init LED PINS
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  // Init RFID-RC522 readers
  for (uint8_t reader = 0; reader < READER_TOTAL; reader++) {
    // buffer
    char buffer[32];

    // Init reader
    sprintf(buffer, "%i | Init reader", reader);
    Serial.println(buffer);

    mfrc522[reader].PCD_Init(sdaPins[reader], RST_PIN);

    // Display reader info
    sprintf(buffer, "%i | ", reader);
    Serial.print(buffer);

    mfrc522[reader].PCD_DumpVersionToSerial();
  }

  Serial.println("Startup finished");
}

//======//
// LOOP //
//======//
void loop() {
  // Check readers for cards
  for (uint8_t reader = 0; reader < READER_TOTAL; reader++) {
    // Check for new cards
    if (!mfrc522[reader].PICC_IsNewCardPresent()) {
      // Set led red
      setLEDColor(255, 0, 0);
      return;
    }

    // Select one of the cards
    if (!mfrc522[reader].PICC_ReadCardSerial()) {
      // Set led red
      setLEDColor(255, 0, 0);
      return;
    }

    // Set led yellow
    setLEDColor(255, 255, 0);

    // Store card UID
    byte uid[mfrc522[reader].uid.size];

    // Display UID
    Serial.print(reader);
    Serial.print(" | ");

    for (int i = 0; i < mfrc522[reader].uid.size; i++) {
      // Copy the UID
      uid[i] = mfrc522[reader].uid.uidByte[i]; // MISSING A 0???

      // Display UID
      Serial.print(uid[i], HEX);
    }
    // End display UID
    Serial.println();

    byte LoadedCards[mfrc522[reader].uid.size][TotalLoadedCards] = {
      {0x04,0xB3,0xB8,0xBA,0x18,0xD1,0x80},
      {0x04,0xB3,0xB8,0xBA,0x18,0x31,0x80}
    };

    // Checking for matches
    for (int i = 0; i < TotalLoadedCards; i++) {
      Serial.print("Checking | ");
      Serial.println(i);
      if ((memcmp(uid, LoadedCards[i], mfrc522[reader].uid.size)) == 0) {
        Serial.println("MATCH");
        // Set led green
        setLEDColor(0, 255, 0);
      } else {
        Serial.println("NO MATCH");
      }
    }

    // Halt PICC
    mfrc522[reader].PICC_HaltA();
  }
}

void setLEDColor(int red, int green, int blue) {
  analogWrite(LED_RED_PIN, red);
  analogWrite(LED_GREEN_PIN, green);
  analogWrite(LED_BLUE_PIN, blue);
}
