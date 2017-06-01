//=======//
// Inits //
//=======//

//------------------------------------//
// Initialize Controller Registration //
//------------------------------------//
void init_Register() {
    controllerToken = EEPROMReadlong(0);
    if (controllerToken == -1) {
        bool status = false;
        do {
            controllerToken = random(0, 1000000);
            Serial.print("Generated new token: ");
            Serial.println(controllerToken);
            status = TokenRegister();
        } while (!status);
    }

    EEPROMWritelong(0, controllerToken);
    Serial.print("Controllers token is: ");
    Serial.println(controllerToken);
}
