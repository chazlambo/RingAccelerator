// Magnet Pins
const int M1 = 4;
const int M2 = 5;
const int M3 = 6;
const int M4 = 7;

// Status LED Pins
const int LED1 = 32;
const int LED2 = 30;
const int LED3 = 36;
const int LED4 = 34;

void magSetup() {
  // Initialize Magnet Pins
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);

  // Initialize Status LED Pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  // Set Magnets to Low
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);

  // Set Status LEDs to Low
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}
