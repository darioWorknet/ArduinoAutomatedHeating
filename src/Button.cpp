#include <Arduino.h>

const int SHORT_PRESS_TIME = 75;
const int LONG_PRESS_TIME = 1000;



class Button
{
    public:
        int pin;

        Button (int _pin){
            pin = _pin;
        }

        int GetStatus () {
            // Returns: 0 not pressed, 1 short press, 2 long press

            if (digitalRead(pin) == LOW) return 0;

            // Get how long button is pressed
            unsigned long pressTime = GetPressTime();

            // Check if it is a short or long press
            if (pressTime >= LONG_PRESS_TIME) return 2;
            if (pressTime >= SHORT_PRESS_TIME) return 1;
            return 0;
        }


        int WaitForPress (unsigned long maxInterval) {
            unsigned long start = millis();
            int buttonStatus;
            while(millis() - start < maxInterval) {
                buttonStatus = GetStatus();
                if (buttonStatus != 0) return buttonStatus;
            }
            return 0;
        }


    private:
        unsigned long GetPressTime () {
            // Get how long button is pressed
            unsigned long start = millis();
            while (digitalRead(pin) == HIGH && millis() - start < LONG_PRESS_TIME);

            return millis() - start;
        }
};
