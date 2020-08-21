int Zahl = 0;
int PWM = 3;
int Lufter = 5;
int i = 0;
int analogValue = 0;
int sensorValue = 0;
int minwert = 150;
int maxwert = 850;
void setup() {

//Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
pinMode(PWM, OUTPUT);
pinMode(Lufter, OUTPUT);
}

void loop() {
i++;
if(i > 15)
{
sensorValue = analogRead(analogValue);
i = 0;
if (sensorValue > maxwert) {
  maxwert = sensorValue;
  }
if (sensorValue < minwert) {
  minwert = sensorValue;
}
}

Zahl = map(sensorValue, minwert, maxwert, 255, 0    );

if(Zahl < 10) {
 Zahl = 0;
 analogWrite(Lufter, 0);
}
else {
  analogWrite(Lufter, 212);
}
analogWrite(PWM, Zahl);
}
