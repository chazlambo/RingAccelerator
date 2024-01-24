// Recalibrate:
// Shows live readings of all sensors and allows user to set calibration values to current reading

void recalibrate(){
    bool recalBool = 1;
    int tempCals[4];
    while(recalBool) {
        // Update sensor reading values
        for(int i=0; i<4; i++){
            sensVals[i] = analogRead(IRPINS[i]);
        }

        // Update Calibrate Values into temporary variable
        getCalVals(tempCals);

        // Redraw screen with new readings
        drawCalibrate(sensVals, tempCals);

        
        if(!digitalRead(BUT1)) { // If top button is pushed
            recalBool = 0;       // End while loop
        }

        if(!digitalRead(BUT3)) {    // If bottom button is pushed
            setCalVals(sensVals);   // Update Calibrated values to current sensor values
        }
    }
    reset();
    return;
}
