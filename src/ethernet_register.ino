//===========//
// Functions //
//===========//

//--------------------//
// Check Cards Access //
//--------------------//
#define debug_TokenRegister
bool TokenRegister() {
    char buffer[64];
    bool status = false;

    sprintf(buffer, "/api/check/controller/token?token=%ld", controllerToken);
    #if defined(debug_TokenRegister)
    Serial.println(buffer);
    #endif

    if (ConnectServer()) {
        if (SendRequest(buffer) && SkipResponseHeaders()) {
            status = AccessCheck_Reponse();
        }
    }
    DisconnectServer();

    return status;
}

//---------------//
// Read response //
//---------------//
//#define debug_AccessCheck_Reponse
bool AccessCheck_Reponse() {

    const size_t bufferSize = JSON_OBJECT_SIZE(1) + 20;
    DynamicJsonBuffer jsonBuffer(bufferSize);

    JsonObject &root = jsonBuffer.parseObject(ethClient);

    if (!root.success()) {
        #if defined(debug_AccessCheck_Reponse)
        Serial.println(F("JSON parsing failed!"));
        #endif

        return false;
    }

    return root["status"];
}
