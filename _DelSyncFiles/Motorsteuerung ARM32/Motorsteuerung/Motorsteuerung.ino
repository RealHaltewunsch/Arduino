// ###Bibliotheken
/*#include <TimerOne.h> //https://www.pjrc.com/teensy/td_libs_TimerOne.html
  #include <TimerThree.h>*/
#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdlib.h>
#include<ADS1115_WE.h>
#include<Wire.h>
#include <PID_v1.h>
//##############################################################################
//####I2C Adressen & AnalogSensor
#define I2C_ADDRESS 0x48
//##############################################################################
//###Pin Zuweisungen
#define Zuendung_PIN_Leuchte PB10
#define ONE_WIRE_BUS PB2      // Data wire is plugged into pin PB2 on the Arduino
#define Notbetrieb_PIN PB1        //Schalter Notbetrieb
#define Bremse_PIN PB0
#define Zuendung_PIN PA7
#define Sportmodus_PIN PA6
#define Uebertemperatur_PIN_Leuchte PA5
#define Sport_Modus_PIN_Leuchte PA4
#define MOSFET_PIN PA3
#define Induktiver_Sensor PA2  //Interruptfähig, für die Drehzahl berechnung
#define Stromregelung_PIN PA1
#define Stromregelung_PIN_Leuchte PA0
#define Notbetrieb_PIN_Leuchte PC15
#define Freigabe_PIN_Leuchte PC14
#define Gaspedal_check_PIN PC13
//##############################################################################
//###Benutzerveränderliche Parameter die die Motorleistung entsprechend beeinflussen
#define MAX_VALUE_SPORT 65535       //100%
#define MAX_VALUE_LOW 32767         //50%
#define MAX_VALUE_NOTBETRIEB 5000  //7,5%
#define MIN_VALUE_SPORT 5000       //7,5%
#define MIN_VALUE_LOW 3276         //2,4%
#define MIN_VALUE_NOTBETRIEB 1000 //1,5%
//##############################################################################
//###Maximal- und Minimalwerte für Temperaturen, nicht verändern
#define MAX_TEMP_AKKU_STARTUP 45
#define MAX_TEMP_AKKU_RUN 50
#define MAX_TEMP_LEISTUNGSELEKTRONIK 100
#define MAX_TEMP_MOTOR 110
#define MIN_TEMP_AKKU 10
//##############################################################################
//###Maximalwer Strom, nur für den PID Regler interessant
#define MAX_VALUE_CURRENT_SPORT 200.0
#define MAX_VALUE_CURRENT_LOW 60.0
#define MAX_VALUE_CURRENT_NOTBETRIEB 20.0
//##############################################################################
//###Anzahl der Erlaubten Fehler bis zum Abschalten der Freigabe
#define Ueberstrom_Zaehler_Speicher 3
#define Uebertemperatur_Zaehler_Speicher 5
#define Untertemperatur_Zaehler_Speicher 5
#define Temperatursensor_Fehler_Zaehler_Speicher 5
#define AnalogSensorFehler_Zaehler_Speicher 5
//GASPEDAL gemessene Spannungen
int GASPEDAL_MAX = 5000;  //Maximalwert der vom gaspedal erreicht werden kann
int GASPEDAL_MIN = 300; //Offset Spannung Gaspedal in mV
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
volatile bool Stromregelung = false;
volatile bool Bremse = true;
volatile bool Zuendung = false;
volatile bool Sport_Modus = false;
volatile bool Notbetrieb = false;
volatile bool Gaspedal_angeschlossen = false;
bool Ueberstrom = true;
bool Uebertemperatur = true;
bool Untertemperatur = false;
bool Temperatursensor_Fehler = true;
bool AnalogSensorFehler = false;
bool Freigabe = false;
bool Temperatur_LED_Zustand = false;
bool Temperatursensor_Fehler_LED_Zustand = false;
//##############################################################################
//###Auflistung der PID Relevanten Parameter
volatile int Sollwert, Sollwert_analog, Sollwert_relativ, Sollwert_absolut = 0;
//##############################################################################
//###Auflistung der PID Relevanten Parameter
double Messwert_Strom, Sollwert_PID, Messwert_Gaspedal;
double Kp = 20.0, Ki = 50.0, Kd = 10.0;
PID StromPID(&Messwert_Strom, &Sollwert_PID, &Messwert_Gaspedal, Kp, Ki, Kd, DIRECT);
//##############################################################################
//###
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
int MAX_VALUE_CURRENT = 0;

volatile uint32_t rev; // Revolution Count
float Reifen_Durchmesser = 0.2; //in Meter
float ReifenxPI = 0.0;
float MinimaleGeschwindigkeit = 0.5; //in Meter pro Sekunde
float Geschwindigkeit_in_kmh = 0;

long int Frequenz_Sport = 10000;
int Frequenz_Low = 5000;
int Frequenz_Notbetrieb = 2000;

unsigned long int currentMillis = 0;
unsigned long int Periode = 0; //Periodendauer in uS, für die PWM interessant
unsigned long int interval_Temperatur_LED = 300; //einmal in der Sekunde blinken
unsigned long int previousMillis_Temperatur_LED = 0; //speichert den Zeitpunkt des letzten durchgehens
unsigned long int interval_Temperatursensor_Fehler_LED = 1000; //einmal in der Sekunde blinken
unsigned long int previousMillis_Temperatursensor_Fehler_LED = 0; //speichert den Zeitpunkt des letzten durchgehens
int Abtastintervall = 0;  //Wichtig für die Drehzahl berechnung, kann 0 bleiben da es in der Setup Funktion berechnet wird
unsigned long int previousMillis_Abtastintervall = 0; //speichert den Zeitpunkt des letzten durchgehens
int interval_Analog_Fehler = 1000;
unsigned long int previousMillis_Analog_Fehler = 0;
int interval_Temperatur = 5000;  //Wichtig für die Drehzahl berechnung
unsigned long int previousMillis_Temperatur = 0; //speichert den Zeitpunkt des letzten durchgehens

unsigned int Interval_auslesen = 250;
unsigned long int Interval_auslesen_verstrichen = 0;
unsigned int Interval_Temperatur = 2500;
unsigned long int Interval_Temperatur_verstrichen = 0;
unsigned long int measureTime = 0;

uint8_t Ueberstrom_Zaehler = 0; //implementiert
uint8_t Uebertemperatur_Zaehler = 0;    //implementiert
uint8_t Untertemperatur_Zaehler = 0;    //implementiert
uint8_t Temperatursensor_Fehler_Zaehler = 0;  //implementiert
uint8_t AnalogSensorFehler_Zaehler = 0;   //implementiert

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//ADS1115_WE adc = ADS1115_WE();
ADS1115_WE adc(I2C_ADDRESS);


void setup() {
  pinMode(Induktiver_Sensor, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Induktiver_Sensor), eineUmdrehung, RISING); //Interrupt am Induktiven Sensor
  pinMode(Bremse_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Bremse_PIN), Bremse_Funktion, RISING); //Interrupt an den BREMSE_PIN
  pinMode(Zuendung_PIN, INPUT_PULLUP);
  pinMode(Zuendung_PIN_Leuchte, OUTPUT);  //Lampe für Zündung ansprechen
  attachInterrupt(digitalPinToInterrupt(Zuendung_PIN), Zuendung_auslesen, CHANGE); //Interrupt an Zündung_Pin
  pinMode(Sportmodus_PIN, INPUT_PULLUP);
  pinMode(Sport_Modus_PIN_Leuchte, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Sportmodus_PIN), Sport_Modus_auslesen, CHANGE); //Interrupt an Sportmodus_Pin
  pinMode(Notbetrieb_PIN, INPUT_PULLUP);
  pinMode(Notbetrieb_PIN_Leuchte, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Notbetrieb_PIN), Notbetrieb_auslesen, CHANGE); //Interrupt an Notbetrieb_PIN
  pinMode(Stromregelung_PIN, INPUT_PULLUP);
  pinMode(Stromregelung_PIN_Leuchte, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Stromregelung_PIN), Stromreglung_auslesen, CHANGE); //Interrupt an Sportmodus_Pin
  pinMode(Gaspedal_check_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Gaspedal_check_PIN), Gaspedal_check, CHANGE);
  pinMode(Uebertemperatur_PIN_Leuchte, OUTPUT); //Fragwürdig ob das so gelöst wird!!
  pinMode(Freigabe_PIN_Leuchte, OUTPUT);
  pinMode(MOSFET_PIN, OUTPUT);
  digitalWrite(MOSFET_PIN, LOW);

  analogWriteResolution (16); //16-bit PWM, 0-65535
  analogWriteFrequency(10000); // PWM Frequenz von 10kHz als Standard

  adc.setVoltageRange_mV(ADS1115_RANGE_6144);   //maximal 5000 mV
  adc.setMeasureMode(ADS1115_CONTINOUS);
  adc.setConvRate(ADS1115_860_SPS);
  StromPID.SetSampleTime(50);

  ReifenxPI = Reifen_Durchmesser * PI;
  Abtastintervall = (Reifen_Durchmesser / MinimaleGeschwindigkeit) * 1000;

  Ueberstrom_Zaehler = Ueberstrom_Zaehler_Speicher - 1;           //Hier wird der Zähler so gesetzt, dass beim Start nur ein Fehler auftreten darf
  Uebertemperatur_Zaehler = Uebertemperatur_Zaehler_Speicher - 1;           //Hier wird der Zähler so gesetzt, dass beim Start nur ein Fehler auftreten darf
  Untertemperatur_Zaehler = Untertemperatur_Zaehler_Speicher - 1;           //Hier wird der Zähler so gesetzt, dass beim Start nur ein Fehler auftreten darf
  Temperatursensor_Fehler_Zaehler = Temperatursensor_Fehler_Zaehler_Speicher - 1;           //Hier wird der Zähler so gesetzt, dass beim Start nur ein Fehler auftreten darf
  AnalogSensorFehler_Zaehler = AnalogSensorFehler_Zaehler_Speicher - 1;           //Hier wird der Zähler so gesetzt, dass beim Start nur ein Fehler auftreten darf

  Lampentest();
  Bremse_Funktion();
  Zuendung_auslesen();
  Ueber_Untertemperatur_auslesen();
  Sport_Modus_auslesen();
  AnalogSensor_Fehler();
  Gaspedal_check();
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
 Zyklische_Aufrufe();

  if (Uebertemperatur) {
    digitalWrite(Uebertemperatur_PIN_Leuchte, HIGH);
  }
  else if (Untertemperatur) {
    Temperatur_LED_blinken(); //LED blinkt schnell
  }
  else if (Temperatursensor_Fehler) {
    Temperatursensor_Fehler_LED_blinken();    //LED blinkt langsam
  }
  else {
    digitalWrite(Uebertemperatur_PIN_Leuchte, LOW);
  }
  if (Freigabe || Zuendung && Notbetrieb) {
    Gaspedal(); //Verändert Sollwert abhängig vom Pedal
  }
  if (Stromregelung) {
    PID_Regler();   //Aktualisiert den Wert Sollwert_PID
  }
  MotorSteuerung();
}


//Strom auslesen

void MotorSteuerung()
{
  if (Freigabe) {
    if (!Stromregelung) {
      analogWrite(MOSFET_PIN, Sollwert);  //Sollwert ist 0 wenn Freigabe nicht erteilt!
    }
    else {
      analogWrite(MOSFET_PIN, Sollwert_PID);
    }
  }
  else if (Zuendung && Notbetrieb) {
    analogWrite(MOSFET_PIN, Sollwert);  //Sollwert wird durch das Umschalten in den Notbetrieb schon limitiert auf die angegebenen Grenzen
  }
  else {
    Sollwert = 0;
    analogWrite(MOSFET_PIN, Sollwert);  //Sollwert ist 0 wenn Freigabe nicht erteilt!
  }
}
