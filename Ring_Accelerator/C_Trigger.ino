// Trigger Mode
// Turns on magnet for a set time after light break sensor is initially tripped and then turns off, even if still tripped.

// Time Variables
unsigned long t_butt_trig = 0;
unsigned long butt_trig_int = 100;

// Delay buffer time variables
unsigned long t_trig_buffer[4];
unsigned long t_butt_trig_buff = 0;
unsigned long t_trip[4];
unsigned long t_trip_buff = 500;


// Variable Delay
unsigned long triggerBuffer = 50;
unsigned long triggerIncrement = 1;
unsigned long triggerIncrementBig = 10;
unsigned long triggerMin = 0;
unsigned long triggerMax = 500;

void trigger() {
  // Read buttons to update delay amount
  if (t_mil - t_butt_trig > buttonDelay) {                 // User interface for changing delay
    t_butt_trig = t_mil;                                   // Update t_old
    if (t_mil - t_butt_trig_buff > butt_trig_int) {        // Integrate button buffer
      if (!digitalRead(BUT1)) {                            // Read top button (0=pressed)
        triggerBuffer += triggerIncrement;                 // Increment delay
        t_butt_trig_buff = t_mil;                          // Update button buffer
        screenDrawn = 0;                                   // Set screen to be redrawn
      }

      if (!digitalRead(BUT3)) {                            // Read left button
        if (triggerBuffer < triggerIncrement) {            // Prevent negative delay
          triggerBuffer = 0;                               // Bind to zero
        }
        else {
          triggerBuffer -= triggerIncrement;                // Decrement delay
        }
        t_butt_trig_buff = t_mil;
        screenDrawn = 0;                                    // Mark screen to be redrawn
      }

      if (!digitalRead(BUT4)) {                            // Read right button
        triggerBuffer += triggerIncrementBig;              // Increment delay
        t_butt_trig_buff = t_mil;
        screenDrawn = 0;                                   // Set screen to be redrawn
      }

      if (!digitalRead(BUT2)) {                            // Read bottom button
        if (triggerBuffer < triggerIncrementBig) {         // Prevent negative delay
          triggerBuffer = 0;
        }
        else {
          triggerBuffer -= triggerIncrementBig;           // Increment delay
        }
        t_butt_trig_buff = t_mil;
        screenDrawn = 0;                                  // Set screen to be redrawn
      }
    }

    // Bind delay amount value
    if (triggerBuffer < triggerMin) {
      triggerBuffer = triggerMin;
    }
    if (triggerBuffer > triggerMax) {
      triggerBuffer = triggerMax;
    }

    if (!screenDrawn) {                                  // If screen hasn't been drawn
      drawTrigger(triggerBuffer);                        // Draw new screen
    }
  }

    t_mil = millis();

  // IR Sensors
  for (int i = 0; i < 4; i++) {                         // Iterates through each magnet
    sensVals[i] = analogRead(IRPINS[i]);                // Reads sensor value and assigns it to array
    if (abs(sensVals[i] - sensCals[i]) > tolerance) {   // If sensor is outside of tolerance away from calibrated value
        if(t_mil - t_trip[i] > t_trip_buff){            // If the trip buffer has elapsed
            t_trip[i] = t_mil;                          // Update the last trip time
            magnetStates[i] = 1;                        // Set the magnet state to HIGH
        }
    }
    if (t_mil - t_trip[i] <= triggerBuffer) {           // If light sensor is not broken but delay time hasn't elapsed
      magnetStates[i] = 1;                              // Keep the magnet on
    }
    else {                                              // Otherwise:
      magnetStates[i] = 0;                              // Turn the magnet off
    }
  }
}
