// Time Variables
unsigned long t1_delayed = 0;
unsigned long t2_delayed = 0;
unsigned long t3_delayed = 0;
unsigned long t4_delayed = 0;
unsigned long t_butt_delayed = 0;

unsigned long butt_delayed_int = 10000;
unsigned long delayed_int = 1000;

unsigned long t1_del_buffer = 0;
unsigned long t2_del_buffer = 0;
unsigned long t3_del_buffer = 0;
unsigned long t4_del_buffer = 0;
unsigned long t_butt_del_buff = 0;


// Variable Delay
unsigned long delayedBuffer = 50000;
unsigned long delayedIncrement = 100;
unsigned long delayedIncrementBig = 10000;
unsigned long delayedMin = 0;
unsigned long delayedMax = 500000;
float displayVal;

void delayed() {
  Serial.println(delayedBuffer);
  // Read buttons to update delay amount
  if (t_mic - t_butt_delayed > buttonDelay) {
    t_butt_delayed = t_mic;  // Update t_old
    if (t_mic - t_butt_del_buff > butt_delayed_int) {      // Integrate button buffer
      if (!digitalRead(BUT1)) {                            // Read top button
        delayedBuffer += delayedIncrement;                 // Increment delay
        t_butt_del_buff = t_mic;
      }

      if (!digitalRead(BUT3)) {                            // Read bottom button
        if(delayedBuffer < delayedIncrement){
          delayedBuffer = 0;
        }
        else {
          delayedBuffer -= delayedIncrement;              // Decrement delay
        }
        t_butt_del_buff = t_mic;
      }

      if (!digitalRead(BUT4)) {                            // Read left button
        delayedBuffer += delayedIncrementBig;              // Increment delay
        t_butt_del_buff = t_mic;
      }

      if (!digitalRead(BUT2)) {                            // Read left button
        if(delayedBuffer < delayedIncrementBig){
          delayedBuffer = 0;
        }
        else {
          delayedBuffer -= delayedIncrementBig;              // Increment delay
        }
        t_butt_del_buff = t_mic;
      }
    }
    // Bind delay amount value
    if (delayedBuffer < delayedMin) {
      delayedBuffer = delayedMin;
    }
    if (delayedBuffer > delayedMax) {
      delayedBuffer = delayedMax;
    }
    displayVal = float(delayedBuffer) / 1000;
    drawDelayed(displayVal);
  }

  // IR Sensor 1
  if (t_mic - t1_delayed >= delayed_int) {
    t1_delayed = t_mic;
    sensVal1 = analogRead(IR1);
    if (detect(sensVal1, sensCal1)) {
      t1_del_buffer = t_mic;
      m1State = 1;
    }
    else if (t_mic - t1_del_buffer <= delayedBuffer) {
      m1State = 1;
    }
    else {
      m1State = 0;
    }
  }

  // IR Sensor 2
  if (t_mic - t2_delayed >= delayed_int) {
    t2_delayed = t_mic;
    sensVal2 = analogRead(IR2);
    if (detect(sensVal2, sensCal2)) {
      t2_del_buffer = t_mic;
      m2State = 1;
    }
    else if (t_mic - t2_del_buffer <= delayedBuffer) {
      m2State = 1;
    }
    else {
      m2State = 0;
    }
  }

  // IR Sensor 3
  if (t_mic - t3_delayed >= delayed_int) {
    t3_delayed = t_mic;
    sensVal3 = analogRead(IR3);
    if (detect(sensVal3, sensCal3)) {
      t3_del_buffer = t_mic;
      m3State = 1;
    }
    else if (t_mic - t3_del_buffer <= delayedBuffer) {
      m3State = 1;
    }
    else {
      m3State = 0;
    }
  }

  // IR Sensor 4
  if (t_mic - t4_delayed >= delayed_int) {
    t4_delayed = t_mic;
    sensVal4 = analogRead(IR4);
    if (detect(sensVal4, sensCal4)) {
      t4_del_buffer = t_mic;
      m4State = 1;
    }
    else if (t_mic - t4_del_buffer <= delayedBuffer) {
      m4State = 1;
    }
    else {
      m4State = 0;
    }
  }
}
