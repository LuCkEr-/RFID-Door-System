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
  //---------//
  // ARDUINO //
  //---------//
  #include <SPI.h>

  //------//
  // RFID //
  //------//
  #include <MFRC522.h>

  //----------//
  // ETHERNET //
  //----------//
  #include <Ethernet.h>

  //-------//
  // MYSQL //
  //-------//
  #include <MySQL_Connection.h>
  //#include <MySQL_Cursor.h>

//=========//
// DEFINES //
//=========//
  //------//
  // RFID //
  //------//
  // RST/Reset | PIN
  #define RST_PIN       2

  // SDA       | PIN
  #define SDA_PIN_1     40
  #define SDA_PIN_2     41

  // Number of readers
  #define READER_TOTAL  1

  //-----//
  // LED //
  //-----//
  #define LED_RED_PIN 12
  #define LED_GREEN_PIN 8
  #define LED_BLUE_PIN 7

//===========//
// INSTANCES //
//===========//
  //------//
  // RFID //
  //------//
  MFRC522 mfrc522[READER_TOTAL];

  //----------//
  // ETHERNET //
  //----------//
  EthernetClient ethernetClient;

  //-------//
  // MYSQL //
  //-------//
  MySQL_Connection mysqlClient((Client *)&ethernetClient);
  //MySQL_Cursor mysqlPos = MySQL_Cursor(&mysqlClient);

//==================//
// GLOBAL VARIABLES //
//==================//
  //------//
  // RFID //
  //------//
  byte sdaPins[] = {SDA_PIN_1, SDA_PIN_2};

  //----------//
  // ETHERNET //
  //----------//
  //byte eth_mac[] = { 0xAD, 0x0L, 0xF0, 0x42, 0x00, 0x69 };
  // Mac address
  byte eth_mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

  // IP address
  byte eth_IP[] = {192, 168, 10, 90};

  //-------//
  // MYSQL //
  //-------//
  // Mysql server ip
  IPAddress mysql_IP(192, 168, 10, 2);

  // Mysql server port
  int mysql_Port = 3066;

  // Mysql user
  char mysql_user[] = "kuristiku";

  // Mysql password
  char mysql_password[] = "eFo04ppjNkG3JJOD";

  //----------------//
  // TESTING VALUES //
  //----------------//
  int TotalLoadedCards = 10;

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

  // Init LED PINS
  Serial.print("Assigning LED outputs...");
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  Serial.println(" [OK]");

  // Init Ethernet
  Serial.print("Init Ethernet...");
  Ethernet.begin(eth_mac, eth_IP);
  Serial.println(" [OK]");

  // Init MYSQL
  Serial.print("Init Mysql...");
  if (mysqlClient.connect(mysql_IP, mysql_Port, mysql_user, mysql_password)) {
    delay(1000);
    // Connection was made
    Serial.println(" [OK]");
  } else {
    // No connection
    Serial.println(" [FAIL]");
    mysqlClient.close();
  }

  // Init SPI bus
  Serial.print("Init SPI...");
  SPI.begin();
  Serial.println(" [OK]");

  // Init RFID-RC522 readers
  Serial.println("Init RFID readers...");
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
  Serial.println("[DONE]");

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
      return;
    }

    // Select one of the cards
    if (!mfrc522[reader].PICC_ReadCardSerial()) {
      return;
    }

    // Set led yellow
    setLEDColor(0, 0, 255);

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
      //Serial.print("Checking | ");
      //Serial.println(i);
      if ((memcmp(uid, LoadedCards[i], mfrc522[reader].uid.size)) == 0) {
        //Serial.println("MATCH");
        // Set led green
        setLEDColor(0, 255, 0);
      } else {
        //Serial.println("NO MATCH");
      }
    }

    // Halt PICC
    mfrc522[reader].PICC_HaltA();

    // Set led red
    setLEDColor(255, 0, 0);
  }
}

void setLEDColor(int red, int green, int blue) {
  analogWrite(LED_RED_PIN, red);
  analogWrite(LED_GREEN_PIN, green);
  analogWrite(LED_BLUE_PIN, blue);
}
