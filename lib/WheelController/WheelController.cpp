#include "WheelController.h"

WheelController::WheelController(uint8_t lf, uint8_t lb, uint8_t rf, uint8_t rb)
    : leftFwd(lf), leftBwd(lb), rightFwd(rf), rightBwd(rb) {}

void WheelController::begin() {
    pinMode(leftFwd, OUTPUT);
    pinMode(leftBwd, OUTPUT);
    pinMode(rightFwd, OUTPUT);
    pinMode(rightBwd, OUTPUT);
    stop();
}

void WheelController::stop() {
    analogWrite(leftFwd, 0);
    analogWrite(leftBwd, 0);
    analogWrite(rightFwd, 0);
    analogWrite(rightBwd, 0);
}

void WheelController::setSpeed(float left, float right) {
    left = constrain(left, -1.0f, 1.0f);
    right = constrain(right, -1.0f, 1.0f);

    int leftPWM = abs(left) * 1023;
    int rightPWM = abs(right) * 1023;

    if (left > 0) {
        analogWrite(leftFwd, leftPWM);
        analogWrite(leftBwd, 0);
    } else if (left < 0) {
        analogWrite(leftFwd, 0);
        analogWrite(leftBwd, leftPWM);
    } else {
        analogWrite(leftFwd, 0);
        analogWrite(leftBwd, 0);
    }

    if (right > 0) {
        analogWrite(rightFwd, rightPWM);
        analogWrite(rightBwd, 0);
    } else if (right < 0) {
        analogWrite(rightFwd, 0);
        analogWrite(rightBwd, rightPWM);
    } else {
        analogWrite(rightFwd, 0);
        analogWrite(rightBwd, 0);
    }
}
