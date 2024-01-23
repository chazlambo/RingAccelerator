// Ring Accelerator Main
// Program made by Charlie Lambert
// Last Revision: 1/22/2024
// Revision Notes:
//    -Added more comments to make code very clear
//    -Removed unnecessary timing function from sense and delay functions
//    -Removed magnet states serial prints
//    -Implement logic to stop redrawing mode menus every loop
//    -Removed reduntant conversion from blinkState bool to blinkVal
//    -Combined individual magnet states and variables into single array and function
//    -Combined magnet stallout variables and code into single array and if statement
//    -Moved magnet state count into B_SetMagnets and modified for simpler implementation
//    -Replaced instances of repeated code with for loops and arrays
//    -Removed unnecessary time interval if statments for main functions
//    -Converted back to milliseconds

// To do:
//    -Add Trigger function which will trigger the magnet for a user defined period of time immediately when light break is broken
//    -Add Calibrate function that will display current calibrated values, current readings, and can set new calibrated values to be saved for later
//        - Use EEPROM?
//    -Add Game function where defaults sense mode but magnets will only turn on if correct button is pressed

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
      manual();
      break;
    case 2:
      sense();
      break;
    case 3:
      delayed();
      break;
    case 4:
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
