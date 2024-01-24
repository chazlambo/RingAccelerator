// B_Reset
// Functions for checking reset conditions and reseting the system.

void resetCheck() {
  // Check if all 4 buttons were pressed
  if (digitalRead(BUT1) || digitalRead(BUT2) || digitalRead(BUT3) || digitalRead(BUT4)) { // If any of the buttons aren't pressed
    return;                                                                               // Don't reset
  }
  else {
    reset();
  }
}
void reset() {// Reset all program variables and return to main menu

  // Menu Navigation Variables
  menuVal = 0;
  blinkState = 0;

  // Reset States and Values
  for(int i = 0; i<4; i++){
    magnetStates[i] = 0;
    sensVals[i] = 0;
  }

  // Turn off magnets and indicators
  setMagnets(magnetStates);

  // Reset Screen Draw Variable
  screenDrawn = 0;

  // State Variables
  menuState = 1;

  // Update Stallout Interval
  runout_int += runout_int_add;

  // Reset Game Score
  gameScore = 0;

  // Reset Buffer Variables
  delayedBuffer = 50;
  triggerBuffer = 50;

  // To do: Add physical connection from reset to pin for full hardware reset
}
