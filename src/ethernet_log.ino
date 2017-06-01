//===========//
// Functions //
//===========//

//-------------------//
// Add entry to logs //
//-------------------//
#define debug_AccessLog
bool AccessLog() {
    char buffer[64];
    bool status = false;

    sprintf(buffer, "/api/log/insert?cardRFID=%s&doorHash=%ld", cReadCard, controllerToken);
    #if defined(debug_AccessLog)
    Serial.println(buffer);
    #endif

    if (ConnectServer()) {
        if (SendRequest(buffer) && SkipResponseHeaders()) {
            status = AccessLog_Reponse();
        }
    }
    DisconnectServer();

    return status;
}

//---------------//
// Read response //
//---------------//
//#define debug_AccessLog_Reponse
bool AccessLog_Reponse() {

    const size_t bufferSize = JSON_OBJECT_SIZE(1) + 20;
    DynamicJsonBuffer jsonBuffer(bufferSize);

    JsonObject &root = jsonBuffer.parseObject(ethClient);

    if (!root.success()) {
        #if defined(debug_AccessLog_Reponse)
        Serial.println(F("JSON parsing failed!"));
        #endif

        return false;
    }

    return root["status"];
}
