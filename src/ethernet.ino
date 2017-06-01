//=======//
// Inits //
//=======//

//--------------------------------//
// Initialize Ethernet Connection //
//--------------------------------//
#define debug_init_Ethernet
void init_Ethernet() {
    #if defined(debug_init_Ethernet)
    Serial.print(F("Init Ethernet"));
    #endif

    int8_t retry = 0;

    do {
        if (Ethernet.begin(ethMac) != 0) {
            eth_Enabled = true;
        } else {
            #if defined(debug_init_Ethernet)
            Serial.print(F("."));
            #endif

            retry++;
        }
    } while (!eth_Enabled && retry < MAX_RETRY);

    if (!eth_Enabled && retry == MAX_RETRY) {
        #if defined(debug_init_Ethernet)
        Serial.println(F(" [FAIL]"));
        Serial.println(F("Rebooting board..."));
        #endif

        delay(2000);
        SoftReboot();
    } else if (eth_Enabled) {
        #if defined(debug_init_Ethernet)
        Serial.println(F(" [OK]"));
        #endif

        // Print IP address
        #if defined(debug_init_Ethernet)
        Serial.print(F("IP Address: "));

        for (int thisByte = 0; thisByte < 4; thisByte++) {
            // print the value of each int of the IP address:
            Serial.print(Ethernet.localIP()[thisByte], DEC);
            Serial.print(F("."));
        }

        Serial.println();
        #endif
    }
}

//===========//
// Functions //
//===========//

//-------------------//
// Connect to server //
//-------------------//
#define debug_ConnectServer
bool ConnectServer() {
    #if defined(debug_ConnectServer)
    Serial.print(F("Connecting to "));
    Serial.print(apiServer);
    Serial.print(F(":"));
    Serial.print(apiServerPort);
    #endif

    bool status = ethClient.connect(apiServer, apiServerPort);

    #if defined(debug_ConnectServer)
    Serial.println(status ? " [OK]" : " [FAIL]");
    #endif

    return status;
}

//------------------//
// Send API request //
//------------------//
//#define debug_SendRequest
//#define debug_SendRequest_response
bool SendRequest(String resource) {
    #if defined(debug_SendRequest)
    Serial.print(F("Sending request..."));
    #endif

    String buffer = F("POST ");
    buffer += resource;
    buffer += F(" HTTP/1.0");
    #if defined(debug_SendRequest)
        Serial.println();
        Serial.println(buffer);
        Serial.print(F("Bytes sent: "));
        Serial.println(ethClient.println(buffer));
    #else
        ethClient.println(buffer);
    #endif

    buffer = F("Host: ");
    buffer += apiServer;
    #if defined(debug_SendRequest)
        Serial.println(buffer);
        Serial.print(F("Bytes sent: "));
        Serial.println(ethClient.println(buffer));
    #else
        ethClient.println(buffer);
    #endif

    buffer = F(
        "Authorization: Bearer TOKEN HERE");
        #if defined(debug_SendRequest)
            Serial.println(buffer);
            Serial.print(F("Bytes sent: "));
            Serial.println(ethClient.println(buffer));
        #else
            ethClient.println(buffer);
        #endif

        buffer = F("Accept: application/json");
        #if defined(debug_SendRequest)
            Serial.println(buffer);
            Serial.print(F("Bytes sent: "));
            Serial.println(ethClient.println(buffer));
        #else
            ethClient.println(buffer);
        #endif

        buffer = "Connection: close";
        #if defined(debug_SendRequest)
            Serial.println(buffer);
            Serial.print(F("Bytes sent: "));
            Serial.println(ethClient.println(buffer));
        #else
            ethClient.println(buffer);
        #endif

        ethClient.println();

        #if defined(debug_SendRequest)
            Serial.println(F(" [OK]"));
        #endif

        #if defined(debug_SendRequest_response)
            Serial.println(F("Waiting for answer"));
            Serial.println();
            Serial.println();
            while (true) {
                if (ethClient.available()) {
                    char c = ethClient.read();
                    Serial.print(c);
                }
            }
        #else
            return true;
        #endif
    }

    //--------------//
    // Skip headers //
    //--------------//
    #define debug_SkipResponseHeaders
    bool SkipResponseHeaders() {
        char endOfHeaders[] = "\r\n\r\n";

        ethClient.setTimeout(apiTimeout);
        bool status = ethClient.find(endOfHeaders);

        #if defined(debug_SkipResponseHeaders)
        if (!status) {
            Serial.println(F("No response or invalid response!"));
        }
        #endif

        return status;
    }

    //---------------------//
    // Print response data //
    //---------------------//
    /*void PrintUserData(const struct UserData *userData) {
        Serial.print("userID = ");
        Serial.println(userData->userID);
        Serial.print("doorID = ");
        Serial.println(userData->doorID);
    }*/

    //------------------------//
    // Disconnect from server //
    //------------------------//
    #define debug_DisconnectServer
    void DisconnectServer() {
        #if defined(debug_DisconnectServer)
        Serial.println("Disconnect");
        #endif

        ethClient.stop();
    }

    //---------------------//
    // Print response data //
    //---------------------//
    void PrintResponseContent() {
        // connectLoop controls the hardware fail timeout
        int connectLoop = 0;

        while (ethClient.connected()) {
            if (ethClient.available()) {
                char c = ethClient.read();
                Serial.print(c);
                // set connectLoop to zero if a packet arrives
                connectLoop = 0;
            }

            connectLoop++;

            // if more than 10000 milliseconds since the last packet
            if (connectLoop > 10000) {
                // then close the connection from this end.
                Serial.println();
                Serial.println(F("Timeout"));
                ethClient.stop();
            }
            // this is a delay for the connectLoop timing
            delay(5);
        }
    }
