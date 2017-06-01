//=======//
// Inits //
//=======//

//------------------//
// Initialize Relay //
//------------------//
#define debug_init_RELAY
void init_RELAY() {
    #if defined(debug_init_RELAY)
    Serial.print(F("Assigning RELAY output..."));
    #endif

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, relayStatus);
    relay_Enabled = true;

    #if defined(debug_init_RELAY)
    Serial.println(F(" [OK]"));
    #endif
}

// Relay timer //
void Relay_Timer() {
    // Only check timer when the relay is enabled
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;
        if (relayStatus) {
            relayStatus = false;
            digitalWrite(RELAY_PIN, relayStatus);
        }
        LED_Status(1);
    }
}
