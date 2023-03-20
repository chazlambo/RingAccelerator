// Time Variables
unsigned long t1_man = 0;
unsigned long t2_man = 0;
unsigned long t3_man = 0;
unsigned long t4_man = 0;
unsigned long manual_int = 100;

void manual() {
  if (t_mic - t1_man >= manual_int) {
    t1_man = t_mic;
    if (!digitalRead(BUT1)) {
      m1State = 1;
    }
    else {
      m1State = 0;
    }
  }

  if (t_mic - t2_man >= manual_int) {
    t2_man = t_mic;
    if (!digitalRead(BUT2)) {
      m2State = 1;
    }
    else {
      m2State = 0;
    }
  }

  if (t_mic - t3_man >= manual_int) {
    t3_man = t_mic;
    if (!digitalRead(BUT3)) {
      m3State = 1;
    }
    else {
      m3State = 0;
    }
  }

  if (t_mic - t4_man >= manual_int) {
    t4_man = t_mic;
    if (!digitalRead(BUT4)) {
      m4State = 1;
    }
    else {
      m4State = 0;
    }
  }
  drawManual();
}
