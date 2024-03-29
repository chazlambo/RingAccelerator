void setupFun() {
  // Initialize Serial Communication
  Serial.begin(9600);

  // Run Magnet Setup Function
  magSetup();

  // Run Sensor Setup Function
  sensSetup();

  // Run the OLED Setup Function
  oledSetup();

  // Retrieve Calibrated Values
  calibrateSetup();

  // Call reset function
  reset();
}
