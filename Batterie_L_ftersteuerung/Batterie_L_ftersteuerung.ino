#include <TimerOne.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdlib.h>
//#############################################################
#define ONE_WIRE_BUS 3      // Data wire is plugged into pin 3 on the Arduino
#define MAX 1023
#define MIN 300
#define AKKU_MIN 35
#define AKKU_MAX 50
//#############################################################
long int Faktor = 1000000;
long int Frequenz = 1000; //Frequenz in Hertz
int Periode = 0; //Periodendauer in uS
int Temperatur_Akkus_1 = 0;
int Temperatur_Akkus_2 = 0;
int Temperatur_Akkus_3 = 0;
int Temperatur_Akkus_Max = 0;
int Temperatur_Akkus_Min = 0;
int Sollwert = 0;
//#############################################################
int PWM_PIN = 10; //Gibt PWM aus
int MOSFET = 8;   //Schaltet Lüfter frei
//#############################################################
uint8_t Temperatursensor_Akkus_1[8] = { 0x28, 0x8A, 0x63, 0x79, 0xA2, 0x00, 0x03, 0x04 };
uint8_t Temperatursensor_Akkus_2[8] = { 0x28, 0x8E, 0x62, 0x79, 0xA2, 0x00, 0x03, 0x15 };
uint8_t Temperatursensor_Akkus_3[8] = { 0x28, 0x45, 0xB5, 0x79, 0xA2, 0x00, 0x03, 0x7D };
//#############################################################

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup() {
  // put your setup code here, to run once:
  Periode = Faktor / Frequenz;
  pinMode(PWM_PIN, OUTPUT);
  pinMode(MOSFET, OUTPUT);
  Timer1.initialize(Periode);
  Timer1.start();
  digitalWrite(MOSFET, HIGH);
  Timer1.pwm(PWM_PIN, MAX);
  delay(3000);
  digitalWrite(MOSFET, LOW);
  Timer1.pwm(PWM_PIN, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Min_Akku_Temperatur_erfragen ()<= 0) {  //Fehler des Temperatursensors
    digitalWrite(MOSFET, HIGH);
    Sollwert = MAX;
    Timer1.pwm(PWM_PIN, Sollwert);
  }
  else if (Max_Akku_Temperatur_erfragen ()>= AKKU_MIN) { //Kühlung einschalten, normales Verhalten
    digitalWrite(MOSFET, HIGH);
    Sollwert = map(Temperatur_Akkus_Max, AKKU_MIN, AKKU_MAX, MIN, MAX);
    Sollwert = constrain(Sollwert, MIN,MAX);
    Timer1.pwm(PWM_PIN, Sollwert);
  }
  else if (Max_Akku_Temperatur_erfragen ()< AKKU_MIN){                              //Kühlung nicht notwendig
    digitalWrite(MOSFET, LOW);
    Sollwert = 0;
    Timer1.pwm(PWM_PIN, Sollwert);
  }
  //Testfunktion();
  //delay(5000);
}
