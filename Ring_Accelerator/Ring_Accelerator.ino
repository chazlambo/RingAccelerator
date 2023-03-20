// Time Variables
unsigned long t_mic;
unsigned long t_run;
unsigned long t_reset;
unsigned long t_stallout;
unsigned long t1_stall;
unsigned long t2_stall;
unsigned long t3_stall;
unsigned long t4_stall;


// Interval Variables
unsigned long run_int = 300;            // microseconds
unsigned long reset_int = 10000;        // microseconds
unsigned long t_magnet_stall = 500000;  // microseconds
unsigned long runout_int = 300000000;   // microseconds

// Program State Variables
int modeState = 0;

// Magnet State Variables
bool m1State = LOW;
bool m2State = LOW;
bool m3State = LOW;
bool m4State = LOW;
int stateCount = 0;

void setup() {
  setupFun();
}

void loop() {
  menu();

  // Update Time
  t_mic = micros();

  if (t_mic - t_run > run_int) {
    
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
    // Update Time
    t_mic = micros();
    
    if(!m1State) {
      t1_stall = t_mic;
    }
    if(!m2State) {
      t2_stall = t_mic;
    }
    if(!m3State) {
      t3_stall = t_mic;
    }
    if(!m4State) {
      t4_stall = t_mic;
    }

    if (t_mic - t1_stall > t_magnet_stall) {
      m1State = 0;
    }
    if (t_mic - t2_stall > t_magnet_stall) {
      m2State = 0;
    }
    if (t_mic - t3_stall > t_magnet_stall) {
      m3State = 0;
    }
    if (t_mic - t4_stall > t_magnet_stall) {
      m4State = 0;
    }

    // Count States to make sure more than 3 don't turn on
    stateCount = 0;
    if(m1State) {
      stateCount += 1;
    }
    if(m2State) {
      stateCount += 1;
    }
    if(m3State) {
      stateCount += 1;
      if (stateCount > 2) {
        m3State = 0;
      }
    }
    if(m4State) {
      stateCount += 1;
      if (stateCount > 2) {
        m4State = 0;
      }
    }

    
    // Set magnet and indicator states
    setM1(m1State);
    setM2(m2State);
    setM3(m3State);
    setM4(m4State);
    Serial.print(m1State);
    Serial.print("\t");
    Serial.print(m2State);
    Serial.print("\t");
    Serial.print(m3State);
    Serial.print("\t");
    Serial.println(m4State);
  }

  if (t_mic - t_reset > reset_int) {  // Reset when all 4 buttons are pressed
    resetCheck();
  }

  if (modeState != 0 && t_mic - t_stallout > runout_int) {  // Resets after 5 minutes of use for safety
    reset();
  }
}
