#include <Arduino.h>
#include <EEPROM.h>

const int BLINK_DELAY = 100;
const int BLINK_TIMES = 3;

// This class allows to control single led
class Led
{
    public:
        int pin;
        int eepos;
        bool status;

        void On() {
            digitalWrite(pin, HIGH);
        }

        void Off() {
            digitalWrite(pin, LOW);
        }

        void ShowStatus() {
            GetStatus();
            status ? On() : Off();
        }

        void GetStatus() {
            EEPROM.get(eepos, status);
        }

        void UpdateStatus() {
            GetStatus();
            EEPROM.update(eepos, !status);
            GetStatus();
        }

        void Blink() {
            for (int i = 0; i < BLINK_TIMES; i++) {
                On();
                delay(BLINK_DELAY);
                Off();
                delay(BLINK_DELAY);
            }
        }
};




// This class has functions to control the leds as a whole
class Leds
{
    public:
        Led leds[7];
        int size;
        int index = 0;

        Leds(int* pins,  int len) {
            size = len;   
            for (int i = 0; i < size; i++)
            {
                leds[i].pin = pins[i];
                leds[i].eepos = i * sizeof(bool);
                leds[i].GetStatus();
            }
        }

        void Next () {
            index = (index+1) % size;
        }

        Led Current () {
            return leds[index];
        }
        
        void Blink() {
            for (int j = 0; j < BLINK_TIMES                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         ; j++) {
                for (int i = 0; i < size; i++) leds[i].On();
                delay(BLINK_DELAY);
                for (int i = 0; i < size; i++) leds[i].Off();
                delay(BLINK_DELAY);
            }
        }

        void TurnOff() {
            for (int i = 0; i < size; i++) leds[i].Off();
        }

        void ShowStatus() {
            for (int i = 0; i < size; i++) leds[i].ShowStatus();
        }
};