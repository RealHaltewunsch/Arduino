// ###Bibliotheken
#include <TimerOne.h> //https://www.pjrc.com/teensy/td_libs_TimerOne.html
#include <TimerThree.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdlib.h>
#include<ADS1115_WE.h>
#include<Wire.h>
//##############################################################################
//####I2C Adressen & AnalogSensor
#define I2C_ADDRESS 0x48
//##############################################################################
//###Pin Zuweisungen
#define Zuendung_PIN_Leuchte 0
#define ONE_WIRE_BUS 1      // Data wire is plugged into pin 1 on the Arduino
#define NOTAUS_PIN 2
#define Bremse_PIN 3
#define Zuendung_PIN 4
#define Sportmodus_PIN 5
#define Uebertemperatur_PIN_Leuchte 6
#define Sport_Modus_PIN_Leuchte 7
#define MOSFET_PIN 10
#define Induktiver_Sensor 18  //Interruptfähig, für die Drehzahl berechnung 
//##############################################################################
//###Benutzerveränderliche Parameter die die Motorleistung entsprechend beeinflussen
#define MAX_VALUE_SPORT 1023
#define MAX_VALUE_LOW 512
#define MIN_VALUE_SPORT 50
#define MIN_VALUE_LOW 25
//##############################################################################
//###Maximal- und Minimalwerte für Temperaturen, nicht verändern
#define MAX_TEMP_AKKU_STARTUP 45
#define MAX_TEMP_AKKU_RUN 50
#define MAX_TEMP_LEISTUNGSELEKTRONIK 100
#define MAX_TEMP_MOTOR 110
#define MIN_TEMP_AKKU 10
//##############################################################################
//###Maximalwer Strom
#define MAX_VALUE_CURRENT_SPORT 300
#define MAX_VALUE_CURRENT_LOW 60
//##############################################################################
//###Offset Spannung Gaspedal in mV
int Offset_Spannung_Gaspedal = 300;
//##############################################################################
//###Auflistung und Zuweisung aller verwendeten Sensoren
uint8_t Temperatursensor_Akkus_1[8] = { 0x28, 0xCE, 0x06, 0x45, 0x92, 0x16, 0x02, 0xF2 };
uint8_t Temperatursensor_Akkus_2[8] = { 0x28, 0xD3, 0x13, 0x79, 0xA2, 0x00, 0x03, 0xD1 };
uint8_t Temperatursensor_Akkus_3[8] = { 0x28, 0x77, 0x10, 0x79, 0xA2, 0x00, 0x03, 0x1F }; //Kabel sind falsch Angschlossen, plus an schwarz und minus an rot
uint8_t Temperatursensor_Motor [8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Leistungselektronik_1 [8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Leistungselektronik_2 [8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//##############################################################################
//###Auflistung und Zuweisung der Zustände
bool NOTAUS = true;
bool Ueberstrom = true;
bool Bremse = true;
bool Zuendung = false;
bool Uebertemperatur = true;
bool Untertemperatur = true;
bool Sport_Modus = false;
bool Temperatursensor_Fehler = true;
bool AnalogSensorFehler = false;

volatile int Stellwert = 0;

int Temperatur_Akkus_1 = 0;
int Temperatur_Akkus_2 = 0;
int Temperatur_Akkus_3 = 0;
int Temperatur_Akkus_Max = 0;
int Temperatur_Akkus_Min = 0;
int Temperatur_Leistungselektronik_1 = 0;
int Temperatur_Leistungselektronik_2 = 0;
int Temperatur_Leistungselektronik_Max = 0;
int Temperatur_Leistungselektronik_Min = 0;
int Temperatur_Motor = 0;

int MAX_VALUE = 0;
int MIN_VALUE = 0;

volatile uint32_t rev; // Revolution Count
float Reifen_Durchmesser = 0.2; //in Meter
float ReifenxPI = 0.0;
int Abtastintervall = 0;
float MinimaleGeschwindigkeit = 0.5; //in Meter pro Sekunde

long int Prescaler = 1000000;
long int Frequenz_Sport = 10000;
long int Frequenz_Low = 5000;

unsigned long int currentTime = 0;
unsigned long int Periode = 0; //Periodendauer in uS

unsigned int Interval_auslesen = 250;
unsigned long int Interval_auslesen_verstrichen = 0;
unsigned int Interval_Temperatur = 2500;
unsigned long int Interval_Temperatur_verstrichen = 0;
unsigned long measureTime = 0;


// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//ADS1115_WE adc = ADS1115_WE();
ADS1115_WE adc(I2C_ADDRESS);


void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(NOTAUS_PIN), NOTAUS_Funktion, RISING); //Interrupt an den NOTAUS PIN
  attachInterrupt(digitalPinToInterrupt(Bremse_PIN), Bremse_Funktion, RISING); //Interrupt an den NOTAUS PIN
  attachInterrupt(digitalPinToInterrupt(Induktiver_Sensor), eineUmdrehung, RISING);
  Timer3.initialize(200000);  //Motorsteuerung mit neuen Werten alle 200ms versorgen
  Timer3.attachInterrupt(MotorSteuerung);
  pinMode(Zuendung_PIN_Leuchte, OUTPUT);  //Lampe für Zündung ansprechen
  pinMode(Uebertemperatur_PIN_Leuchte, OUTPUT);
  pinMode(MOSFET_PIN, OUTPUT);
  pinMode(Sport_Modus_PIN_Leuchte, OUTPUT);
  pinMode(NOTAUS_PIN, INPUT_PULLUP);
  pinMode(Bremse_PIN, INPUT);
  pinMode(Zuendung_PIN, INPUT_PULLUP);
  pinMode(Sportmodus_PIN, INPUT_PULLUP);
  pinMode(Induktiver_Sensor, INPUT); // Interrupt 0


  adc.setVoltageRange_mV(ADS1115_RANGE_6144);   //maximal 5000 mVadc.setConvRate(ADS1115_250_SPS);              //250 mal die Sekunde updaten
  adc.setMeasureMode(ADS1115_CONTINOUS);
  adc.setConvRate(ADS1115_860_SPS);

  ReifenxPI = Reifen_Durchmesser * PI;
  Abtastintervall = (Reifen_Durchmesser / MinimaleGeschwindigkeit) * 1000;

  Lampentest();
  NOTAUS_auslesen();
  Bremse_auslesen();
  Zuendung_auslesen();
  Uebertemperatur_Startup_auslesen();
  Untertemperatur_auslesen();
  Sport_Modus_auslesen();
  Sport_Modus_firstscan();
  TemperaturSensorFehler();
  AnalogSensor_Fehler();


}
//ToDo
//Strombegrenzung implementieren
//niedrige Temperatur Strombegrenzung
//Code aufräumen und Übersichtlicher machen
//Alles auf einem Bildschirm ausgeben



void loop() {
  // put your main code here, to run repeatedly:
  NOTAUS_auslesen();
  Zuendung_auslesen();
  Sport_Modus_auslesen();
  Bremse_auslesen();
  Uebertemperatur_auslesen();
  Untertemperatur_auslesen();
  TemperaturSensorFehler();
}

//Strom auslesen

void MotorSteuerung(void)
{
  adc.setCompareChannels(ADS1115_COMP_2_GND);
  if (!NOTAUS && !Ueberstrom && !Bremse && Zuendung && !Uebertemperatur && !Untertemperatur && !AnalogSensorFehler && !Temperatursensor_Fehler) {
    Stellwert = adc.getResult_mV(); // alternative: getResult_mV for Millivolt
    Stellwert = constrain(Stellwert, 0, 5000);
    if (Stellwert > Offset_Spannung_Gaspedal) {
      Stellwert = map (Stellwert, 0, 5000, MIN_VALUE, MAX_VALUE);
    }
    else {
      Stellwert = 0;
    }
  }
  else {
    Stellwert = 0;
  }
  Timer1.pwm(MOSFET_PIN, Stellwert);
}
