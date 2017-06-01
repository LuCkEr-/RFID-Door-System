//===========//
// Functions //
//===========//

//--------------------//
// Check Cards Access //
//--------------------//
#define debug_CheckPermission
bool CheckPermission() {
    char buffer[64];
    bool status = false;

    sprintf(buffer, "/api/card/get/permission?cardRFID=%s", cReadCard);
    #if defined(debug_CheckPermission)
    Serial.println(buffer);
    #endif

    if (ConnectServer()) {
        if (SendRequest(buffer) && SkipResponseHeaders()) {
            status = CheckPermission_Reponse();
        }
    }
    DisconnectServer();

    return status;
}

//---------------//
// Read response //
//---------------//
//#define debug_CheckPermission_Reponse
bool CheckPermission_Reponse() {

    const size_t bufferSize = JSON_OBJECT_SIZE(1) + 20;
    DynamicJsonBuffer jsonBuffer(bufferSize);

    JsonObject &root = jsonBuffer.parseObject(ethClient);

    if (!root.success()) {
        #if defined(debug_CheckPermission_Reponse)
        Serial.println(F("JSON parsing failed!"));
        #endif

        return false;
    }

    return root["status"];
}
