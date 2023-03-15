void resetCheck() {
  // Check if all 4 buttons were pressed
  if (digitalRead(BUT1) || digitalRead(BUT2) || digitalRead(BUT3) || digitalRead(BUT4)) {
    return;
  }
  else {
    Serial.println("RESET");
    reset();
  }
}
void reset() {
  // Reset all program variables
  // Menu Navigation Variables
  menuVal = 0;
  blinkVal = 0;
  blinkState = 0;

  // Sensor Value Variables
  sensVal1 = 0;
  sensVal2 = 0;
  sensVal3 = 0;
  sensVal4 = 0;

  // Reset magnet states
  m1State = 0;
  m2State = 0;
  m3State = 0;
  m4State = 0;

  // Turn off magnets and indicators
  setM1(m1State);
  setM2(m2State);
  setM3(m3State);
  setM4(m4State);

  // State Variables
  menuState = 1;
}
