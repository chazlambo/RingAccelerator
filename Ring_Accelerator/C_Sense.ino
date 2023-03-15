// Time Variables
unsigned long t1_sense = 0;
unsigned long t2_sense = 0;
unsigned long t3_sense = 0;
unsigned long t4_sense = 0;
unsigned long sense_int = 1;

void sense() {
    // IR Sensor 1
    if (t_mil - t1_sense >= sense_int) {  
    t1_sense = t_mil;
    sensVal1 = analogRead(IR1);
    if (detect(sensVal1, sensCal1)) {
      m1State = 1;
    }
    else {
      m1State = 0;
    }
  }

  // IR Sensor 2
  if (t_mil - t2_sense >= sense_int) {
    t2_sense = t_mil;
    sensVal2 = analogRead(IR2);
    if (detect(sensVal2, sensCal2)) {
      m2State = 1;
    }
    else {
      m2State = 0;
    }
  }

  // IR Sensor 3
  if (t_mil - t3_sense >= sense_int) {
    t3_sense = t_mil;
    sensVal3 = analogRead(IR3);
    if (detect(sensVal3, sensCal3)) {
      m3State = 1;
    }
    else {
      m3State = 0;
    }
  }

  // IR Sensor 4
  if (t_mil - t4_sense >= sense_int) {
    t4_sense = t_mil;
    sensVal4 = analogRead(IR4);
    if (detect(sensVal4, sensCal4)) {
      m4State = 1;
    }
    else {
      m4State = 0;
    }
  }
  drawSense();
}
