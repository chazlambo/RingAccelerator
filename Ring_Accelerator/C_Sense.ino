// Sense Mode:
// Triggers magnets whenever light break sensors are triggered

void sense() {

  for (int i = 0; i < 4; i++) {                         // For each IR Sensor
    sensVals[i] = analogRead(IRPINS[i]);                // Read the value of the pin
    if (abs(sensVals[i] - sensCals[i]) > tolerance) {   // If value is outside of tolerance from calibrated value
      magnetStates[i] = 1;                              // Set magnet state to HIGH
    }
    else {                                              // If value is inside tolerance from calibrated value
      magnetStates[i] = 0;                              // Set magnet state to LOW
    }
  }

  if (!screenDrawn) { // If the screen hasn't already been drawn
    drawSense();      // Draws the sense menu
    screenDrawn = 1;  // Set the screen drawn boolean to true
  }
}
