// Game Mode:
// Triggers magnets whenever light break sensors are triggered and button is pressed

void game() {

  for (int i = 0; i < 4; i++) {                         // For each IR Sensor
    sensVals[i] = analogRead(IRPINS[i]);                // Read the value of the pin
    if (abs(sensVals[i] - sensCals[i]) > tolerance) {   // If value is outside of tolerance from calibrated value
      if(!digitalRead(BUTPINS[i])){                     // If correct button is pressed
        magnetStates[i] = 1;                            // Set magnet state to HIGH
        gameScore++;                                    // Increment game score
        screenDrawn = 0;                                // Mark screen for update
      }
      else {                                            // If correct button is not pressed
        magnetStates[i] = 0;                            // Set magnet state to LOW
        gameScore = 0;                                  // Reset the game score to zero
        screenDrawn = 0;                                // Mark screen for update
      }
      
    }
    else {                                              // If value is inside tolerance from calibrated value
      magnetStates[i] = 0;                              // Set magnet state to LOW
    }
  }

  if (!screenDrawn) {         // If the screen hasn't already been drawn
    drawGame(gameScore);      // Draws the sense menu
    screenDrawn = 1;          // Set the screen drawn boolean to true
  }
}

