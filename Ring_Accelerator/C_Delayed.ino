// Delayed Mode
// Turns on magnets whenever light break sensors are triggered and delays turning magnet off by a user set delay

// Time Variables
unsigned long t_butt_delayed = 0;
unsigned long butt_delayed_int = 100;

// Delay buffer time variables
unsigned long t_del_buffer[4];
unsigned long t_butt_del_buff = 0;


// Variable Delay
unsigned long delayedBuffer = 50;
unsigned long delayedIncrement = 1;
unsigned long delayedIncrementBig = 10;
unsigned long delayedMin = 0;
unsigned long delayedMax = 500;

void delayed() {
  // Read buttons to update delay amount

  if (t_mil - t_butt_delayed > buttonDelay) { // User interface for changing delay
    t_butt_delayed = t_mil;  // Update t_old
    if (t_mil - t_butt_del_buff > butt_delayed_int) {      // Integrate button buffer
      if (!digitalRead(BUT1)) {                            // Read top button (0=pressed)
        delayedBuffer += delayedIncrement;                 // Increment delay
        t_butt_del_buff = t_mil;                           // Update button buffer
        screenDrawn = 0;                                   // Set screen to be redrawn
      }

      if (!digitalRead(BUT3)) {                            // Read left button
        if (delayedBuffer < delayedIncrement) {            // Prevent negative delay
          delayedBuffer = 0;
        }
        else {
          delayedBuffer -= delayedIncrement;              // Decrement delay
        }
        t_butt_del_buff = t_mil;
        screenDrawn = 0;                                   // Set screen to be redrawn
      }

      if (!digitalRead(BUT4)) {                            // Read right button
        delayedBuffer += delayedIncrementBig;              // Increment delay
        t_butt_del_buff = t_mil;
        screenDrawn = 0;                                   // Set screen to be redrawn
      }

      if (!digitalRead(BUT2)) {                            // Read bottom button
        if (delayedBuffer < delayedIncrementBig) {         // Prevent negative delay
          delayedBuffer = 0;
        }
        else {
          delayedBuffer -= delayedIncrementBig;             // Increment delay
        }
        t_butt_del_buff = t_mil;
        screenDrawn = 0;                                   // Set screen to be redrawn
      }
    }

    // Bind delay amount value
    if (delayedBuffer < delayedMin) {
      delayedBuffer = delayedMin;
    }
    if (delayedBuffer > delayedMax) {
      delayedBuffer = delayedMax;
    }

    if (!screenDrawn) {         // If screen hasn't been drawn
      drawDelayed(delayedBuffer);  // Draw new screen
    }
  }

  // IR Sensors
  for (int i = 0; i < 4; i++) {                         // Iterates through each magnet
    sensVals[i] = analogRead(IRPINS[i]);                // Reads sensor value and assigns it to array
    if (abs(sensVals[i] - sensCals[i]) > tolerance) {   // If sensor is outside of tolerance away from calibrated value
      t_del_buffer[i] = t_mil;                          // Update the delay buffer time
      magnetStates[i] = 1;                              // Set the magnet state to HIGH
    }
    else if (t_mil - t_del_buffer[i] <= delayedBuffer) { // If light sensor is not broken but delay time hasn't elapsed
      magnetStates[i] = 1;                              // Keep the magnet on
    }
    else {                                              // Otherwise:
      magnetStates[i] = 0;                              // Turn the magnet off
    }
  }
}
