// A_SENSORS
// File for storing sensor specific variables and functions

// IR LED Pins
const int IR1 = A0;
const int IR2 = A1;
const int IR3 = A2;
const int IR4 = A3;
const int IRPINS[] = {IR1, IR2, IR3, IR4};

// Button Pins
const int BUT1 = 48;
const int BUT2 = 42;
const int BUT3 = 44;
const int BUT4 = 46;
const int BUTPINS[] = {BUT1, BUT2, BUT3, BUT4};

// Sensor Calibration Values
int sensCal1 = 309;
int sensCal2 = 266;
int sensCal3 = 288;
int sensCal4 = 190;
int sensCals[] = {sensCal1, sensCal2, sensCal3, sensCal4};
int tolerance = 50;

// Sensor Value Variables
int sensVals[4];

// Button Pressed Variables
bool but1 = 0;
bool but2 = 0;
bool but3 = 0;
bool but4 = 0;

void sensSetup() {
  // Initialize Button Pins
  for (int i = 0; i < 4; i++) {
    pinMode(BUTPINS[i], INPUT_PULLUP); // Sets the default value to HIGH unless button is pressed connecting it to ground
    // INPUT_PULLUP uses internal pullup resistors so default is HIGH, and when pressed is 1
  }
}

bool detect(int val, int cal) {     // Simple function for detecting if a light break sensor is being triggered
  if (abs(val - cal) > tolerance) { // If the current value is more than (tolerance) units away from the calibrated value
    return 1;                       // Detection
  }
  return 0;                         // Otherwise no detection
}
