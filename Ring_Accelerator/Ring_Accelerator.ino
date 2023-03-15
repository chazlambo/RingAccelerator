// Time Variables
unsigned long t_mil;
unsigned long t_run;
unsigned long t_reset;
unsigned long t_stallout;

// Interval Variables
unsigned long run_int = 2;
unsigned long reset_int = 10;

// Program State Variables
int modeState = 0;

// Magnet State Variables
int m1State = LOW;
int m2State = LOW;
int m3State = LOW;
int m4State = LOW;

void setup() {
  setupFun();

}

void loop() {
  menu();

  // Update Time
  t_mil = millis();

  if (t_mil - t_run > run_int) {
    
    // Get magnet states based on selected mode
    switch (modeState) {
      case 1:
        manual();
        break;
      case 2:
        sense();
        break;
      case 3:
        delayed();
        break;
      case 4:
        break;
      default:
        break;
    }

    // Set magnet and indicator states
    setM1(m1State);
    setM2(m2State);
    setM3(m3State);
    setM4(m4State);
  }

  if (t_mil - t_reset > reset_int) {  // Reset when all 4 buttons are pressed
    resetCheck();
  }

  if (modeState != 0 && t_mil - t_stallout > 300000) {  // Resets after 5 minutes of use for safety
    reset();
  }
}
