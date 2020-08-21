#define SS_RELAY_PIN 6
#define BLAU  3
#define GRUEN 4
#define ROT   5

#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdlib.h>
#define ONE_WIRE_BUS 2      // Data wire is plugged into pin 2 on the Arduino
int Setpoint = 22;
int Temperatur = 0;

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup()
{
  //initialize the variables we're linked to

  pinMode(BLAU, OUTPUT);
  pinMode(GRUEN, OUTPUT);
  pinMode(ROT, OUTPUT);
  pinMode(SS_RELAY_PIN, OUTPUT);
  digitalWrite(SS_RELAY_PIN, HIGH);
  delay(5000);
  Serial.begin(9600);
}

void loop()
{
  Zweipunktregler();
  LED_Anzeige();
  
}

void Zweipunktregler() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  Temperatur = (int)sensors.getTempCByIndex(0); //Temperatur wird weiter verwendet
  if (Temperatur == -127){
    digitalWrite(SS_RELAY_PIN, HIGH);
    delay(2000);
    digitalWrite(SS_RELAY_PIN, LOW);
    delay(2000);
  }
  else if (Temperatur <= Setpoint - 1) {
    digitalWrite(SS_RELAY_PIN, HIGH);
  }
  else if (Temperatur >= Setpoint + 1) {
    digitalWrite(SS_RELAY_PIN, LOW);
  }
  
  Serial.println(Temperatur);
  //Serial.println(digitalRead(SS_RELAY_PIN));
}

void LED_Anzeige() {
  if (Temperatur < Setpoint - 1) {
    digitalWrite(BLAU, HIGH);
    digitalWrite(ROT, LOW);
    digitalWrite(GRUEN, LOW);
  }
  else if (Temperatur > Setpoint + 1) {
    digitalWrite(ROT, HIGH);
    digitalWrite(BLAU, LOW);
    digitalWrite(GRUEN, LOW);
  }
  else {
    digitalWrite(GRUEN, HIGH);
    digitalWrite(ROT, LOW);
    digitalWrite(BLAU, LOW);
  }

}
