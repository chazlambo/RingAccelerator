// A_Calibrate
// File for the basic EEPROM calibration functions

#include <EEPROM.h>

// Sensor Calibration Values
int sensCal1 = 309;
int sensCal2 = 266;
int sensCal3 = 288;
int sensCal4 = 190;
int sensCals[] = {sensCal1, sensCal2, sensCal3, sensCal4};
int tolerance = 50;

// EEPROM Variables
int eeAddress = 0; //EEPROM address of first calibration value

void calibrateSetup() {
    getCalVals(sensCals);
}

void setCalVals(int vals[]) {                        // Writes integer array to calibrated values
  int addressIndex = 0;                                 // Start at address 0
  for (int i = 0; i < 4; i++){                          // Iterate through each sensor
    EEPROM.write(addressIndex, vals[i] >> 8);        // Write first byte of int
    EEPROM.write(addressIndex + 1, vals[i] & 0xFF);  // Write 2nd byte of int
    addressIndex += 2;                                  // Move to next int address
  }
}

void getCalVals(int calnums[]) {                        
  int addressIndex = 0;                                                             // Start at address 0
  for (int i = 0; i < 4; i++) {                                                     // Iterate through each sensor
    calnums[i] = (EEPROM.read(addressIndex) << 8) + EEPROM.read(addressIndex + 1);  // Read first and second byte of int
    addressIndex += 2;                                                              // Update address to next int
  }
}
