//=======//
// Inits //
//=======//

//------------------------//
// Initialize LED Outputs //
//------------------------//
#define debug_init_LED
void init_LED() {
    #if defined(debug_init_LED)
    Serial.print(F("Assigning LED outputs..."));
    #endif

    pinMode(LED_BLUE_PIN, OUTPUT);
    pinMode(LED_YELLOW_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);
    led_Enabled = true;

    #if defined(debug_init_LED)
    Serial.println(F(" [OK]"));
    #endif
}

//===========//
// Functions //
//===========//

//----------------//
// Set LED Status //
//----------------//
void LED_Status(int status) {
    if (led_Enabled) {
        switch (status) {
            case 1: {
                // Access Granted | Only Blue
                analogWrite(LED_BLUE_PIN, 255);
                analogWrite(LED_YELLOW_PIN, 0);
                analogWrite(LED_RED_PIN, 0);
                break;
            }
            case 2: {
                // Verifing | Only Yellow
                analogWrite(LED_BLUE_PIN, 0);
                analogWrite(LED_YELLOW_PIN, 255);
                analogWrite(LED_RED_PIN, 0);
                break;
            }
            case 3: {
                // Access Denied | Only Red
                analogWrite(LED_BLUE_PIN, 0);
                analogWrite(LED_YELLOW_PIN, 0);
                analogWrite(LED_RED_PIN, 255);
                break;
            }
        }
    }
}
