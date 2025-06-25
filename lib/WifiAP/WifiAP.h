#pragma once
class WifiAP {
    public:
        static void initialize(const char* ssidPrefix, const char* password, short maxConnection);
};