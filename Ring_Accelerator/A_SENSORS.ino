// IR LED Pins
const int IR1 = A0;
const int IR2 = A1;
const int IR3 = A2;
const int IR4 = A3;

// Button Pins
const int BUT1 = 48;
const int BUT2 = 42;
const int BUT3 = 44;
const int BUT4 = 46;

// Sensor Calibration Values
int sensCal1 = 309;
int sensCal2 = 266;
int sensCal3 = 288;
int sensCal4 = 190;
int tolerance = 50;

// Sensor Value Variables
int sensVal1 = 0;
int sensVal2 = 0;
int sensVal3 = 0;
int sensVal4 = 0;

// Button Value Variables
bool but1 = 0;
bool but2 = 0;
bool but3 = 0;
bool but4 = 0;

void sensSetup() {
  // Initialize Button Pins
  pinMode(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT_PULLUP);
  pinMode(BUT3, INPUT_PULLUP);
  pinMode(BUT4, INPUT_PULLUP);
}

bool detect(int val, int cal) {
  if (abs(val - cal) > tolerance) {
    return 1;
  }
  return 0;
}
