#pragma once
#include <WheelController.h>

class WebServer{
    public:
        static void initialize(WheelController& wheel);
        static void loop();
};