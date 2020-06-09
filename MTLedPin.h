#ifndef MEULTRONIX_LED_PIN_H
#define MEULTRONIX_LED_PIN_H

class LedPin {

private:
    int mPin;
    bool mEnabled;

public:
    LedPin(int pin);
    void setEnabled(bool enabled);

};

#endif