const int IR1 = A0;
const int IR2 = A1;
const int IR3 = A2;
const int IR4 = A3;

int sensVal1 = 0;
int sensVal2 = 0;
int sensVal3 = 0;
int sensVal4 = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);
}

void loop() {
  sensVal1 = analogRead(IR1);
  sensVal2 = analogRead(IR2);
  sensVal3 = analogRead(IR3);
  sensVal4 = analogRead(IR4);
  Serial.print("1: ");
  Serial.print(sensVal1);
  Serial.print("\t");
  Serial.print("2: ");
  Serial.print(sensVal2);
  Serial.print("\t");
  Serial.print("3: ");
  Serial.print(sensVal3);
  Serial.print("\t");
  Serial.print("4: ");
  Serial.println(sensVal4);

  delay(2);
}
