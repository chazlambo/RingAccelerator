// B_SetMagnets
// Function for turning individual magnets on or off

void setMagnets(int states[4]) { // Sets the state of Magnet 1

  // Initialize variable to count how many magnets are on
  int stateCount = 0;

  for (int i = 0; i < 4; i++) {         // Iterate through each magnet

    if (states[i] && stateCount < 2) {  // If state is HIGH and less than 2 magnets are turned on
      digitalWrite(LEDPINS[i], HIGH); // Turn on the indicator LED
      digitalWrite(MAGPINS[i], HIGH); // Turn on the magnet
      stateCount++;                   // Add to state count
      // Note: This gives magnets 1 and 2 priority over magnets 3 and 4.
    }
    else {                              // If state is LOW
      digitalWrite(LEDPINS[i], LOW);  // Turn off indicator LED
      digitalWrite(MAGPINS[i], LOW);  // Turn off magnet
    }
  }
}
