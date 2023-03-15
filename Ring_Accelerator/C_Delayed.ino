// Time Variables
unsigned long t1_delayed = 0;
unsigned long t2_delayed = 0;
unsigned long t3_delayed = 0;
unsigned long t4_delayed = 0;
unsigned long t_butt_delayed = 0;

unsigned long but_delayed_int = 10;
unsigned long delayed_int = 1;

unsigned long t1_del_buffer = 0;
unsigned long t2_del_buffer = 0;
unsigned long t3_del_buffer = 0;
unsigned long t4_del_buffer = 0;
unsigned long t_butt_del_buff = 0;
unsigned long delayedBuffer = 50;

void delayed() {
  Serial.println(delayedBuffer);
  // Read buttons to update delay amount
  if (t_mil - t_butt_delayed > buttonDelay) {
    t_butt_delayed = t_mil;  // Update t_old
    if (t_mil - t_butt_del_buff > 100) { // Integrate button buffer
      if (!digitalRead(BUT1)) {               // Read left button
        delayedBuffer += 10;                  // Go back a screen

        t_butt_del_buff = t_mil;
      }

      if (!digitalRead(BUT3)) {               // Read right button
        delayedBuffer -= 10;                 // Go forward a screen
        t_butt_del_buff = t_mil;
      }
    }
    // Bind delay amount value
    if (delayedBuffer < 10) {
      delayedBuffer = 10;
    }
    if (delayedBuffer > 500) {
      delayedBuffer = 500;
    }
    drawDelayed(delayedBuffer);
  }
  
  // IR Sensor 1
  if (t_mil - t1_delayed >= delayed_int) {
    t1_delayed = t_mil;
    sensVal1 = analogRead(IR1);
    if (detect(sensVal1, sensCal1)) {
      t1_del_buffer = t_mil;
      m1State = 1;
    }
    else if (t_mil - t1_del_buffer <= delayedBuffer) {
      m1State = 1;
    }
    else {
      m1State = 0;
    }
  }

  // IR Sensor 2
  if (t_mil - t2_delayed >= delayed_int) {
    t2_delayed = t_mil;
    sensVal2 = analogRead(IR2);
    if (detect(sensVal2, sensCal2)) {
      t2_del_buffer = t_mil;
      m2State = 1;
    }
    else if (t_mil - t2_del_buffer <= delayedBuffer) {
      m2State = 1;
    }
    else {
      m2State = 0;
    }
  }

  // IR Sensor 3
  if (t_mil - t3_delayed >= delayed_int) {
    t3_delayed = t_mil;
    sensVal3 = analogRead(IR3);
    if (detect(sensVal3, sensCal3)) {
      t3_del_buffer = t_mil;
      m3State = 1;
    }
    else if (t_mil - t3_del_buffer <= delayedBuffer) {
      m3State = 1;
    }
    else {
      m3State = 0;
    }
  }

  // IR Sensor 4
  if (t_mil - t4_delayed >= delayed_int) {
    t4_delayed = t_mil;
    sensVal4 = analogRead(IR4);
    if (detect(sensVal4, sensCal4)) {
      t4_del_buffer = t_mil;
      m4State = 1;
    }
    else if (t_mil - t4_del_buffer <= delayedBuffer) {
      m4State = 1;
    }
    else {
      m4State = 0;
    }
  }
}
