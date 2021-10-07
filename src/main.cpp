#include <Arduino.h>
#include "Leds.cpp"
#include "Button.cpp"

#define BUTTON_PIN 9
#define INTERVAL_MS 5000 // Max time without activity to standby

// Leds definition
bool editStatus = false;
int ledPins [] = {2, 3, 4, 5, 6, 7, 8};
int len = sizeof(ledPins) / sizeof(*ledPins);
// Create leds object
Leds leds = Leds(ledPins, len);
// Create button object
Button button = Button(BUTTON_PIN);


void setup() {
  // Set led pins as output
  for (int i = 0; i < len; i++){
    pinMode(ledPins[i], OUTPUT);
  }
  // Set button pin as input
  pinMode(BUTTON_PIN, INPUT);
  // Blink all leds
  leds.Blink();
  Serial.begin(9600);
  Serial.println("Starting program");
}

// Edit leds one by one
void editLed() {
  leds.TurnOff();
  int pressType;
  // This loop breaks when no button is pressed for INTERVAL_MS
  while (true) {
    leds.Current().Blink();
    leds.Current().ShowStatus();
    // Wait until button is pressed
    pressType = button.WaitForPress(INTERVAL_MS);
    // Check how button has been pressed
    if (pressType == 0) break;
    if (pressType == 1){
      leds.Current().Off();
      leds.Next();
    }
    if (pressType == 2) leds.Current().UpdateStatus(); // Store to EEPROM

  }
}


void editLeds() {
  leds.Blink();
  leds.ShowStatus();
  
  while (true) {
    // Wait for button short press
    int pressType = button.WaitForPress(INTERVAL_MS);
    // If button is short pressed edit current led
    if (pressType == 1)
      editLed();
    // Else exit
    else
      break;
  }
  leds.Blink();
}


void loop() {
  if (editStatus) {
    editStatus = false;
    editLeds();
    leds.index = 0;
  } else {
    leds.TurnOff();
    editStatus = button.GetStatus() == 2 ? true : false;
  }
}