void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A1, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //
  T13_on();
  T9_on();
  T11_on();
}



void T1_off() {
  digitalWrite(A1, LOW);
}
void T1_on() {
  digitalWrite(A1, HIGH);
}
void T2_off() {
  digitalWrite(2, LOW);
}
void T2_on() {
  digitalWrite(2, HIGH);
}
void T3_off() {
  digitalWrite(3, LOW);
}
void T3_on() {
  digitalWrite(3, HIGH);
}
void T4_off() {
  digitalWrite(4, LOW);
}
void T4_on() {
  digitalWrite(4, HIGH);
}
void T5_off() {
  digitalWrite(5, LOW);
}
void T5_on() {
  digitalWrite(5, HIGH);
}
void T6_off() {
  digitalWrite(6, LOW);
}
void T6_on() {
  digitalWrite(6, HIGH);
}
void T7_off() {
  digitalWrite(7, LOW);
}
void T7_on() {
  digitalWrite(7, HIGH);
}
void T8_off() {
  digitalWrite(8, LOW);
}
void T8_on() {
  digitalWrite(8, HIGH);
}
void T9_off() {
  digitalWrite(9, LOW);
}
void T9_on() {
  digitalWrite(9, HIGH);
}
void T10_off() {
  digitalWrite(10, LOW);
}
void T10_on() {
  digitalWrite(10, HIGH);
}
void T11_off() {
  digitalWrite(11, LOW);
}
void T11_on() {
  digitalWrite(11, HIGH);
}
void T12_off() {
  digitalWrite(12, LOW);
}
void T12_on() {
  digitalWrite(12, HIGH );
}
void T13_off() {
  digitalWrite(13, LOW);
}
void T13_on() {
  digitalWrite(13, HIGH);
}
