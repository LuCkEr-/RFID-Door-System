//=======//
// Inits //
//=======//

//----------------------//
// Initialize RESET Pin //
//----------------------//
#define debug_init_RESET
void init_RESET() {
    #if defined(init_RESET)
    Serial.print(F("Assigning RESET output..."));
    #endif

    digitalWrite(RESET_PIN, HIGH);
    pinMode(RESET_PIN, OUTPUT);

    #if defined(init_RESET)
    Serial.println(F(" [OK]"));
    #endif
}

//===========//
// Functions //
//===========//

//-------------//
// Sorf reboot //
//-------------//
void SoftReboot() {
    LED_Status(3);
    delay(500);
    digitalWrite(RESET_PIN, LOW);
}
