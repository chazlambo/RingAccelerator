// Time Variables
unsigned long t_menu = 0;
unsigned long t_blink = 0;
unsigned long t_butt_menu = 0;
unsigned long t_butt_buff = 0;

// Time Intervals
unsigned long menuInterval = 10000;
unsigned long blinkDelay = 800000;
unsigned long buttonDelay = 10000;
unsigned long buttonBuffer = 200000;

// Navigation Variables
int menuVal = 0;
int blinkVal = 0;

// State Variables
bool menuState = 1;
bool blinkState = 0;

/******* Menu BMP Array Values *******
 *  0 - Select Mode
 *  1 - Select Mode (Arrows)
 *  2 - Manual
 *  3 - Manual (Arrows)
 *  4 - Sense
 *  5 - Sense (Arrows)
 *  6 - Delay
 *  7 - Delay (Arrows)
 *  8 - Tuned
 *  9 - Tuned (Arrows)
 */

void menu() {
  while(menuState) {
  t_mic = micros(); // Update Time

  // Read button inputs
  if (t_mic - t_butt_menu > buttonDelay) {    
    t_butt_menu = t_mic;  // Update t_old
    if (t_mic - t_butt_buff > buttonBuffer) { // Integrate button buffer
      
      if (!digitalRead(BUT2)) {               // Read left button
        menuVal = menuVal - 2;                // Go back a screen
        t_butt_buff = t_mic;
      }
      
      if (!digitalRead(BUT4)) {               // Read right button
        menuVal = menuVal + 2;                // Go forward a screen
        t_butt_buff = t_mic;
      }
      
      if (!digitalRead(BUT3)) {               // Read bottom button
        if (menuVal > 1 && menuVal < 10) {    // If on a selectable mode
          modeState = menuVal/2;              // Set the global modeState
          menuState = 0;                      // End while loop in loop() function and start main function
        }
      }
    }
  }

  // Arrow Blinking Timer
  if (t_mic - t_blink > blinkDelay) {
    t_blink = t_mic;
    blinkState = !blinkState; // Toggle blink

    // Assign blink value to add later
    if (blinkState) {
      blinkVal = 1;
    }
    else {
      blinkVal = 0;
    }
  }

  // Menu Update
  if (t_mic - t_menu > menuInterval) {
    t_menu = t_mic;
    if (menuVal < 0) {  // Loop to end
      menuVal = 8;
    }
    if (menuVal > 8) {  // Loop to start
      menuVal = 0;
    }

    // Display menu BMP according to value and blink status
    drawMenu(menuVal + blinkVal);
  }
}
}
