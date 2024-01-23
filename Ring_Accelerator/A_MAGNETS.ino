// A_MAGNETS
// File for storing magnet specific functions and variables

// Magnet Pins
const int M1 = 4;
const int M2 = 5;
const int M3 = 6;
const int M4 = 7;
const int MAGPINS[] = {M1, M2, M3, M4};

// Status LED Pins
const int LED1 = 36;
const int LED2 = 34;
const int LED3 = 40;
const int LED4 = 38;
const int LEDPINS[] = {LED1, LED2, LED3, LED4};

void magSetup() { // Setup function for magnet and LED pins
  for (int i = 0; i < 4; i++) {
    pinMode(MAGPINS[i], OUTPUT);
    digitalWrite(MAGPINS[i], LOW);
    pinMode(LEDPINS[i], OUTPUT);
    digitalWrite(LEDPINS[i], LOW);
  }
}
