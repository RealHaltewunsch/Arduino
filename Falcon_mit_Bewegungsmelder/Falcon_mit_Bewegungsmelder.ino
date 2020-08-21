int sensor = 7; // Pin an dem der Sensor angeschlossen ist
int led = 13; // Pin der internen LED, LED leuchtet, wenn Anwesenheit festgestellt wird
int blau = 3; //Pin Blau
int rot = 5; //Pin Rot
int weiss = 6; // Pin Weiss
int anwesend = 0; //nicht verändern/ nicht von Interesse
unsigned long previousMillis = 0; //nicht verändern/ nicht von Interesse
const long interval = 10000; //Dauer bis die Lichter ausgeschaltet wurden, nachdem das letzte Signal gekommen ist (in Millisekunden)
unsigned long currentMillis = 0; // nicht verändern/ nicht von Interesse



void setup() {
  // put your setup code here, to run once:
pinMode(sensor, INPUT);
pinMode(led, OUTPUT);
pinMode(blau, OUTPUT);
pinMode(weiss, OUTPUT);
pinMode(rot, OUTPUT);
Serial.begin(9600);
randomSeed(analogRead(0));

}

void loop() {
  // put your main code here, to run repeatedly:
int sensorstate = digitalRead(sensor);
Serial.println(sensorstate);
int random1 = random (0, 20);
int random2 = random (30, 255);
int random3 = random (0,100);
int random4 = random (125, 200);
//Zeitgeber
      currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;
      anwesend = 0;}
//Zeitgeber

switch (sensorstate){
case 1: anwesend = 1;
        digitalWrite(led, HIGH);
        previousMillis = currentMillis;
        break;
case 0: digitalWrite(led, LOW);
        break;
}
switch (anwesend){
case 1: analogWrite(blau, random1);
        analogWrite(rot, random2);
        if (random3 >= 99){
          analogWrite(weiss, random4);
          }
        else
        {analogWrite(weiss,0);
        }
        break;
case 0: 
        digitalWrite(led, LOW);
        analogWrite(weiss, 0);
        analogWrite(blau, 0);
        analogWrite(rot, 0);
        break;
}
delay(50);
}
