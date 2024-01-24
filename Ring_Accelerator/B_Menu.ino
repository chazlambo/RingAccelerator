// B_Menu
// File for the menu function and related variables

// Time Variables
unsigned long t_menu = 0;
unsigned long t_blink = 0;
unsigned long t_butt_menu = 0;
unsigned long t_butt_buff = 0;

// Time Intervals
unsigned long menuInterval = 100;   // Time between each main menu refresh
unsigned long blinkDelay = 800;     // Time between each arrow blink on menu
unsigned long buttonDelay = 50;     // Time between each time buttons are checked
unsigned long buttonBuffer = 300;   // Time until button can be read again, prevents unintentional multiple inputs

// Navigation Variables
int menuVal = 0;

// State Variables
bool menuState = 1;
bool blinkState = 0;

/******* Menu BMP Array Values *******
    0 - Select Mode
    1 - Select Mode (Arrows)
    2 - Game
    3 - Game (Arrows)
    4 - Sense
    5 - Sense (Arrows)
    6 - Delay
    7 - Delay (Arrows)
    8 - Trigger
    9 - Trigger (Arrows)
    10 - Manual
    11 - Manual (Arrows)
    12 - Recalibrate
    13 - Recalibrate (Arrows)
*/

void menu() {
  while (menuState) { // While loop for menu
    t_mil = millis();   // Update Time

    // Read button inputs
    if (t_mil - t_butt_menu > buttonDelay) {    // If buttonDelay microseconds have passed since last check
      t_butt_menu = t_mil;                      // Update last checked time variable
      if (t_mil - t_butt_buff > buttonBuffer) { // Integrate button buffer, prevents reading multiple inputs too quickly

        if (!digitalRead(BUT2)) {               // Read left button
          menuVal = menuVal - 2;                // Go back a screen
          t_butt_buff = t_mil;
        }

        if (!digitalRead(BUT4)) {               // Read right button
          menuVal = menuVal + 2;                // Go forward a screen
          t_butt_buff = t_mil;
        }

        if (!digitalRead(BUT3)) {                              // Read bottom button
          if (menuVal > 1 && menuVal < bmp_menuArray_LEN) {    // If on a selectable mode
            modeState = menuVal / 2;                           // Set the global modeState
            menuState = 0;                                     // End while loop in loop() function and start main function
          }
        }
      }
    }

    // Arrow Blinking Timer
    if (t_mil - t_blink > blinkDelay) { // If blinkDelay microseconds have passed
      t_blink = t_mil;                  // Update last time checked variabel
      blinkState = !blinkState;         // Toggle blink
    }

    // Menu Update
    if (t_mil - t_menu > menuInterval) {  // If menuInterval microseconds have elapsed
      t_menu = t_mil;                     // Update last checked variable
      if (menuVal < 0) {                  // If going before first state
        menuVal = bmp_menuArray_LEN-2;    // Loop to last state
      }
      if (menuVal > bmp_menuArray_LEN-2) {  // If going past last state
        menuVal = 0;                        // Loop to first state
      }

      // Display menu BMP according to value and blink status
      drawMenu(menuVal + blinkState);
    }
  }
}
