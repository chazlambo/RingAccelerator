void setM1(bool state) {
  if(state) {
    digitalWrite(LED1, HIGH);
    digitalWrite(M1, HIGH);
    return;
  }
  digitalWrite(LED1, LOW);
  digitalWrite(M1, LOW);
}

void setM2(bool state) {
  if(state) {
    digitalWrite(LED2, HIGH);
    digitalWrite(M2, HIGH);
    return;
  }
  digitalWrite(LED2, LOW);
  digitalWrite(M2, LOW);
}

void setM3(bool state) {
  if(state) {
    digitalWrite(LED3, HIGH);
    digitalWrite(M3, HIGH);
    return;
  }
  digitalWrite(LED3, LOW);
  digitalWrite(M3, LOW);
}

void setM4(bool state) {
  if(state) {
    digitalWrite(LED4, HIGH);
    digitalWrite(M4, HIGH);
    return;
  }
  digitalWrite(LED4, LOW);
  digitalWrite(M4, LOW);
}
