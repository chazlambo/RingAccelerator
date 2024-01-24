// Ring Accelerator Main
// Program made by Charlie Lambert
// Last Revision: 1/24/2024
// Revision Notes:
//    -Added Game Function
//    -Added Trigger Function
//    -Add Recalibrate function that will 
//        -Display current calibrated values
//        -Display current readings
//        -Set new calibrated values to be saved for later
//    -Created new BMP's for menus
//    -Reordered Menu: Select -> Game -> Sense -> Delay -> Trigger -> Manual -> Recalibrate
//    -Updated menu with new modes

// To do:
//    -(Optional) Add wire for reset pin. (Probably won't do this and will just power cycle if needed)

// Notes:
//    -Files are named with alphabetical prefixes for arduino compiler
//    -Arduino compiles everything A-Zwith the main file being compiled first

// Time Variables
unsigned long t_mil;      // Current time in milliseconds
unsigned long t_reset;    // Last reset check time in milliseconds
unsigned long t_stallout; // Variable for tracking full system timeout
unsigned long t_stall[4]; // Variable for tracking magnets timeout

// Interval Variables
unsigned long reset_int = 100;              // Time in milliseconds between instances of checking if all buttons are pressed for reset
unsigned long t_magnet_stall = 1000;        // Time in milliseconds that a magnet can be on before it stalls out
unsigned long runout_int_add = 600000;      // Time in milliseconds until program times out and resets
unsigned long runout_int = runout_int_add;  // Variable to track new reset interval

// Program State Variables
int modeState = 0;
bool screenDrawn = 0;

// Magnet State Variables
int magnetStates[4];

// Game Score Variable
int gameScore = 0;

void setup() {
  setupFun();
}

void loop() {

  menu(); // Runs menuing function to get modeState for main program.

  // Update Time Variable
  t_mil = millis();

  // Get magnet states based on selected mode
  switch (modeState) {  // modeState set by menu() function
    case 1:
      game();
      break;
    case 2:
      sense();
      break;
    case 3:
      delayed();
      break;
    case 4:
      trigger();
      break;
    case 5:
      manual();
      break;
    case 6:
      recalibrate();
      return;
      break;
    default:
      break;
  }

  // Update Time Variable
  t_mil = millis();


  // Implement individual magnet stall out
  for (int i = 0; i < 4; i++) {                 // Iterate through each magnet
    if (!magnetStates[i]) {                     // If a magnet is off
      t_stall[i] = t_mil;                       // Update stall start time
    }
    if (t_mil - t_stall[i] > t_magnet_stall) {  // If the magnet has been on longer than t_magnet_stall
      magnetStates[i] = 0;                      // Turn off that magnet
    }
  }

  // Set magnet and indicator states
  setMagnets(magnetStates);

  if (t_mil - t_reset > reset_int) {  // Reset to menu if all 4 buttons are pressed
    resetCheck();
  }

  if (modeState != 0 && t_mil - t_stallout > runout_int) {  // Resets back to start after certain amount of time has passed
    reset();
  }
}
