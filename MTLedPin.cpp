#include <Arduino.h>

#include "MTLedPin.h"

LedPin::LedPin(int pin)
{
    mPin = pin;

    pinMode(pin, OUTPUT);
}

void LedPin::setEnabled(bool enabled)
{
    this->mEnabled = enabled;
    digitalWrite(mPin, this->mEnabled ? HIGH : LOW);
}