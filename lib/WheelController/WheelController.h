#pragma once
#include <Arduino.h>

class WheelController {
private:
    uint8_t leftFwd, leftBwd, rightFwd, rightBwd;

public:
    WheelController(uint8_t lf, uint8_t lb, uint8_t rf, uint8_t rb);
    void begin();
    void stop();
    void setSpeed(float left, float right);
};
