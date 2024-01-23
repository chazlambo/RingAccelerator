// Manual Mode:
// Magnets turn on whenever button is pressed

// Time Variables
unsigned long t_man[4];
unsigned long manual_int = 1;

void manual() {
  t_mil = millis(); // Update time

  for (int i = 0; i < 4; i++) {
    if (t_mil - t_man[i] >= manual_int) { // If manual_int milliseconds has passed since button i was last checked
      t_man[i] = t_mil;                   // Update time variable
      if (!digitalRead(BUTPINS[i])) {     // If button i is pressed
        magnetStates[i] = 1;              // Turn on magnet i
      }
      else {                              // If button i is not pressed
        magnetStates[i] = 0;              // Turn off magnet i
      }
    }
  }

  if (!screenDrawn) { // If the screen hasn't already been drawn
    drawManual();     // Draws the sense menu
    screenDrawn = 1;  // Set the screen drawn boolean to true
  }
}
