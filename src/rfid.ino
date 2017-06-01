//=======//
// Inits //
//=======//

//------------------------//
// Initialize Card Reader //
//------------------------//
#define debug_init_RFID
void init_RFID() {
    #if defined(debug_init_RFID)
    Serial.print(F("Init reader..."));
    #endif

    RFID.PCD_Init();

    #if defined(debug_init_RFID)
    Serial.println(F(" [OK]"));
    #endif

    ShowReaderDetails();
}

//===========//
// Functions //
//===========//

//---------------------//
// Convert UID to CHAR //
//---------------------//
void GetChar(byte array[], char *buffer) {
    int i;
    for (i = 0; i < 4; i++) {
        sprintf(buffer + i * 2, "%02X", array[i]);
    }
    buffer[i * 2] = 0;
}

//-----------------//
// Read PICC's UID //
//-----------------//
bool GetID() {
    // If a new PICC placed to RFID reader continue
    if (!RFID.PICC_IsNewCardPresent()) {
        return false;
    }

    // Since a PICC placed get Serial and continue
    if (!RFID.PICC_ReadCardSerial()) {
        return false;
    }

    for (uint8_t i = 0; i < 4; i++) {
        readCard[i] = RFID.uid.uidByte[i];
        Serial.print(readCard[i] < 0x10 ? " 0" : " ");
        Serial.print(readCard[i], HEX);
    }

    GetChar(readCard, cReadCard);

    Serial.println(F(""));

    // Stop reading
    RFID.PICC_HaltA();

    return true;
}

//----------------------------//
// Show Card Reader's Details //
//----------------------------//
void ShowReaderDetails() {
    // Get the MFRC522 software version
    byte v = RFID.PCD_ReadRegister(RFID.VersionReg);

    Serial.print(F("MFRC522 Software Version: 0x"));
    Serial.print(v, HEX);

    if (v == 0x91)
    Serial.print(F(" = v1.0"));
    else if (v == 0x92)
    Serial.print(F(" = v2.0"));
    else
    Serial.print(F(" (unknown),probably a chinese clone?"));

    Serial.println(F(""));

    // When 0x00 or 0xFF is returned, communication probably failed
    if ((v == 0x00) || (v == 0xFF)) {
        Serial.println(F(
            "WARNING: Communication failure, is the MFRC522 properly connected?"));
            Serial.println(F("SYSTEM HALTED: Check connections."));

            // do not go further
            while (true)
            ;
        }
    }
