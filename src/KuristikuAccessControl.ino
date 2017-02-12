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
  #include <Ethernet2.h>

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
  #define LED_BLUE_PIN 7
  #define LED_YELLOW_PIN 8
  #define LED_RED_PIN 12

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
  // Mac address
  byte eth_mac[] = { 0xAD, 0x07, 0xF0, 0x42, 0x00, 0x69 };

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
  Serial.begin(115200);

  // Wait while the serial port is being opened
  while (!Serial);
  Serial.println();
  Serial.println("Starting...");

  // Init LED PINS
  init_LED();

  // Init Ethernet
  init_Ethernet();

  // Init MYSQL
  init_Mysql();

  // Init SPI bus
  Serial.print("Init SPI...");
  SPI.begin();
  Serial.println(" [OK]");

  // Init Rfid readers
  init_Rfid();

  Serial.println("Startup finished");
}

//=======//
// Inits //
//=======//
void init_LED() {
  Serial.print("Assigning LED outputs...");
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  Serial.println(" [OK]");
}

void init_Ethernet() {
  Serial.print("Init Ethernet...");

  if (Ethernet.begin(eth_mac) != 0) {
    // Connection was made
    Serial.println(" [OK]");
  } else {
    // No connection
    Serial.println(" [FAIL]");
  }

  // Print IP address
  Serial.print("IP Address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
}

void init_Mysql () {
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
}

void init_Rfid() {
  for (uint8_t reader = 0; reader < READER_TOTAL; reader++) {
    // buffer
    char buffer[32];

    // Init reader
    sprintf(buffer, "%i | Init reader...", reader);
    Serial.print(buffer);

    mfrc522[reader].PCD_Init(sdaPins[reader], RST_PIN);

    Serial.println(" [OK]");

    // Display reader info
    sprintf(buffer, "%i | ", reader);
    Serial.print(buffer);

    mfrc522[reader].PCD_DumpVersionToSerial();
  }
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

    // Verifing
    LED_Status(2);

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
        // Access Granted
        LED_Status(1);
      } else {
        //Serial.println("NO MATCH");
      }
    }

    // Halt PICC
    mfrc522[reader].PICC_HaltA();

    // Access Denied
    LED_Status(3);
  }
}

void LED_Status(int status) {
  switch(status) {
    case 1: {
      // Access Granted
      analogWrite(LED_BLUE_PIN, HIGH);
      analogWrite(LED_YELLOW_PIN, LOW);
      analogWrite(LED_RED_PIN, LOW);
      break;
    }
    case 2: {
      // Verifing
      analogWrite(LED_BLUE_PIN, LOW);
      analogWrite(LED_YELLOW_PIN, HIGH);
      analogWrite(LED_RED_PIN, LOW);
      break;
    }
    case 3: {
      // Access Denied
      analogWrite(LED_BLUE_PIN, LOW);
      analogWrite(LED_YELLOW_PIN, LOW);
      analogWrite(LED_RED_PIN, HIGH);
      break;
    }
  }
}
