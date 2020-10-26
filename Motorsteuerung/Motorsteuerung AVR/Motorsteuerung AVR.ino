//Board: STM32F4 series
//Board part number: BlackPillF411CE
//UART Support enabled (generic 'Serial')
//USB Support CDC, generic Serial supersede UART
//STM32CubeProgrammer (DFU)
//STM32 Core V1.90

//DIP Schalter Leistungselektronik
//1 OFF
//2 OFF
//3 OFF   Peak-Current on
//4 ON    UART Simple Mode
//Potentiometer 1 -> Im Uhrzeigersinn bis zum Anschlag
//Potentiometer 2 -> Gegen Uhrzeigersinn bis zum Anschlag
//Potentiometer 3 -> Gegen Uhrzeigersinn bis zum Anschlag

// ###Bibliotheken
#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdlib.h>
#include<ADS1115_WE.h>
#include<Wire.h>
#include "ssd1306.h"
#include <SoftwareSerial.h>
//##############################################################################
//####I2C Adressen & AnalogSensor
#define I2C_ADDRESS 0x48    //Adresse für den AnalogSensor
//STM32: B7(SDA), B6(SCL) //für den Display und analog Sensor interessant
//##############################################################################
//###Pin Zuweisungen
//Interrupt Pins sind Multiplexed, es gibt nur 0 bis 15, PB2 darf bei Boot nicht HIGH sein
//Vergeben: 0;1;2;4;5;6;7;13
//RX PB3
//TX PA15
#define Zuendung_PIN_Leuchte PB10
#define Notbetrieb_PIN PB1        //Schalter Notbetrieb
#define Enable_Pin PB2
#define Bremse_PIN PB0
#define Zuendung_PIN PA7
#define Sportmodus_PIN PA6
#define ONE_WIRE_BUS PA5      // Data wire is plugged into pin PA5 on the STM32
#define Enable_Pin PA3
#define Uebertemperatur_PIN_Leuchte PA2
#define Sport_Modus_PIN_Leuchte PA1
#define Regenerativbremsen_PIN PA4
#define Regenerativbremsen_PIN_Leuchte PA0
#define Notbetrieb_PIN_Leuchte PC15
#define Freigabe_PIN_Leuchte PC14
#define Gaspedal_check_PIN PC13
#define TestLED_PIN PB12
#define MOSFET PA15
//##############################################################################
//###Maximal- und Minimalwerte für Temperaturen, nicht verändern
#define MAX_TEMP_AKKU_STARTUP 45
#define MAX_TEMP_AKKU_RUN 50
#define MAX_TEMP_MOTOR 110
#define MIN_TEMP_AKKU 10
//##############################################################################
//###Maximalwer Strom, interessant für Den Betriebsmodi, wird per TX/RX übertragen
#define MAX_VALUE_CURRENT_SPORT 200
#define MAX_VALUE_CURRENT_LOW 60
#define MAX_VALUE_CURRENT_NOTBETRIEB 80   //hier Strom eintragen <------------------------------------------------------------------------------------------------------
//##############################################################################
//GASPEDAL gemessene Spannungen
int GASPEDAL_MAX = 3827;  //Maximalwert der vom gaspedal erreicht werden kann <-----------------------------------------------------------------------------------------
int GASPEDAL_MIN = 916; //Offset Spannung Gaspedal in mV  <-------------------------------------------------------------------------------------------------------------
//##############################################################################
//###Auflistung und Zuweisung aller verwendeten Sensoren
uint8_t Temperatursensor_Akku_1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_2[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_3[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_4[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_5[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_6[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Motor[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//uint8_t Temperatursensor_Leistungselektronik_1 [8] = { 0x28, 0xD3, 0x13, 0x79, 0xA2, 0x00, 0x03, 0xD1 };
//uint8_t Temperatursensor_Leistungselektronik_2 [8] = { 0x28, 0xCE, 0x06, 0x45, 0x92, 0x16, 0x02, 0xF2 };
//uint8_t Temperatursensor_Leistungselektronik_3 [8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
// 0x28, 0x77, 0x10, 0x79, 0xA2, 0x00, 0x03, 0x1F //Kabel sind falsch Angschlossen, plus an schwarz und minus an rot
//##############################################################################
//###Auflistung und Zuweisung der Zustände
//volatile bool Stromregelung = false;
volatile bool Bremse = true;
volatile bool Zuendung = false;
volatile bool Sport_Modus = false;
volatile bool Notbetrieb = false;
//volatile bool Gaspedal_angeschlossen = false;
const bool Gaspedal_angeschlossen = true;
bool Uebertemperatur = true;
bool Untertemperatur = false;
bool Temperatursensor_Fehler = true;
bool AnalogSensorFehler = false;
bool Freigabe = false;
bool Temperatur_LED_Zustand = false;
bool Temperatursensor_Fehler_LED_Zustand = false;
bool TestLED = false;
bool Regenerativbremsen = false;
//OLED Fehler beseitgen und dabei wenig Speicher und Rechenzeit benötigende Variablen
bool Geschwindigkeit_gross_alt = false; //verwirrendes Konzept, aber das wird benötigt, da sonst ein Anzeigefehler ensteht wenn man von einer einstellingen Geschwindigkeit zu einer zweistelligen Geschwindigkeit wechselt
bool Geschwindigkeit_gross = false; //verwirrendes Konzept, aber das wird benötigt, da sonst ein Anzeigefehler ensteht wenn man von einer einstellingen Geschwindigkeit zu einer zweistelligen Geschwindigkeit wechselt
bool Geschwindigkeit_Vorzeichen_alt = false; //verwirrendes Konzept, aber das wird benötigt, da sonst ein Anzeigefehler ensteht wenn man von negativ zu positiv wechselt...
bool Geschwindigkeit_Vorzeichen = false; //verwirrendes Konzept, aber das wird benötigt, da sonst ein Anzeigefehler ensteht wenn man von negativ zu positiv wechselt...
bool OLED_Reset = false;
bool OLED_Reset_alt = false;
//##############################################################################
int Temperatur_Akku_1 = 0;
int Temperatur_Akku_2 = 0;
int Temperatur_Akku_3 = 0;
int Temperatur_Akku_4 = 0;
int Temperatur_Akku_5 = 0;
int Temperatur_Akku_6 = 0;
int Temperatur_Akku_Max = 0;
int Temperatur_Akku_Min = 0;
int Temperatur_Motor = 0;
int Temperatur_Leistungselektronik = 0;
int Temperatur_Leistungselektronik_hex = 0;
int Temperaturzaehler = 0;

int Sollwert_analog = 0;
int Sollwert_relativ = 0;
int Sollwert_pwm = 0;
int Sollwert_hex = 0x00;

int Strom = 0;
int Strom_hex = 0x00;

int Batteriespannung = 0;
int Batteriespannung_hex = 0x00;

int Leistung = 0;

unsigned long int currentMillis = 0;
const unsigned long int interval_Temperatur_LED = 300; //dreimal in der Sekunde blinken
unsigned long int previousMillis_Temperatur_LED = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned long int interval_Temperatursensor_Fehler_LED = 1000; //einmal in der Sekunde blinken
unsigned long int previousMillis_Temperatursensor_Fehler_LED = 0; //speichert den Zeitpunkt des letzten durchgehens
const int interval_Analog_Fehler = 1000;
unsigned long int previousMillis_Analog_Fehler = 0;
const int interval_Temperatur = 1000;  //Wichtig für die Temp Messung
unsigned long int previousMillis_Temperatur = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_OLED = 500;  //Wichtig für den OLED 1000 ist auch gut
unsigned long int previousMillis_OLED = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_Batteriespannung = 2000;  //Wichtig für die Batteriespannung
unsigned long int previousMillis_Batteriespannung = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_LED = 250;  //Wichtig für die Batteriespannung
unsigned long int previousMillis_LED = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_OLED_reset = 60000;  //Wichtig für's entfernen von unvorhersehbaren Fehlern
unsigned long int previousMillis_OLED_reset = 0; //speichert den Zeitpunkt des letzten durchgehens

const unsigned int Interval_auslesen = 250;
unsigned long int Interval_auslesen_verstrichen = 0;
const unsigned int Interval_Temperatur = 2500;
unsigned long int Interval_Temperatur_verstrichen = 0;
unsigned long int measureTime = 0;

uint8_t Uebertemperatur_Zaehler = 0;    //implementiert
uint8_t Untertemperatur_Zaehler = 0;    //implementiert
uint8_t Temperatursensor_Fehler_Zaehler = 0;  //implementiert
uint8_t AnalogSensorFehler_Zaehler = 0;   //implementiert

int Uebertemperatur_Zaehler_Speicher = 5;
int Untertemperatur_Zaehler_Speicher = 5;
int Temperatursensor_Fehler_Zaehler_Speicher = 5;
int AnalogSensorFehler_Zaehler_Speicher = 5;

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

ADS1115_WE adc(I2C_ADDRESS);

//SoftwareSerial SoftSerial(PA15, PB3); // RX, TX

void setup() {
  /*SoftSerial.begin(9600); //Kommunikation mit Leistungselektronik PA15&PB3
    SoftSerial.write((byte)0xE0);    //UART Mode
    SoftSerial.write((byte)0x8A);    //Direction
    SoftSerial.write((byte)0x01);//forward
    SoftSerial.write((byte)0x80);  //speed
    SoftSerial.write((byte)0x7F);  //100%
    delay(2000);
    SoftSerial.write((byte)0x8A);    //Direction
    SoftSerial.write((byte)0x00);    // STOP   0x01 Forward; 0x02 Regen
  */

  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();

  pinMode(Bremse_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Bremse_PIN), Bremse_Auslesen, CHANGE); //Interrupt an den BREMSE_PIN
  pinMode(Zuendung_PIN, INPUT_PULLUP);
  pinMode(Zuendung_PIN_Leuchte, OUTPUT);  //Lampe für Zündung ansprechen
  attachInterrupt(digitalPinToInterrupt(Zuendung_PIN), Zuendung_auslesen, CHANGE); //Interrupt an Zündung_Pin
  pinMode(Sportmodus_PIN, INPUT_PULLUP);
  pinMode(Sport_Modus_PIN_Leuchte, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Sportmodus_PIN), Sport_Modus_auslesen, CHANGE); //Interrupt an Sportmodus_Pin
  pinMode(Notbetrieb_PIN, INPUT_PULLUP);
  pinMode(Notbetrieb_PIN_Leuchte, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Notbetrieb_PIN), Notbetrieb_auslesen, CHANGE); //Interrupt an Notbetrieb_PIN
  pinMode(Gaspedal_check_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Gaspedal_check_PIN), Gaspedal_check, CHANGE);
  pinMode(Regenerativbremsen_PIN, INPUT_PULLUP);
  pinMode(Regenerativbremsen_PIN_Leuchte, OUTPUT);  //Lampe für Regenerativbremsen ansprechen
  attachInterrupt(digitalPinToInterrupt(Regenerativbremsen_PIN), Regenerativbremsen_Auslesen, CHANGE); //Regenerativbremsen_PIN
  pinMode(Uebertemperatur_PIN_Leuchte, OUTPUT);
  pinMode(Freigabe_PIN_Leuchte, OUTPUT);
  pinMode(TestLED_PIN, OUTPUT);

  pinMode(MOSFET, OUTPUT);

  analogWriteResolution (10); //10-bit PWM, 0-1023
  analogWriteFrequency(1000); // PWM Frequenz von 1kHz als Standard
  Wire.begin();
  adc.init();
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);   //maximal 5000 mV
  adc.setConvRate(ADS1115_860_SPS);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc.setMeasureMode(ADS1115_SINGLE);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);

  Uebertemperatur_Zaehler = Uebertemperatur_Zaehler_Speicher - 1;           //Hier wird der Zähler so gesetzt, dass beim Start nur ein Fehler auftreten darf
  Untertemperatur_Zaehler = Untertemperatur_Zaehler_Speicher - 1;           //Hier wird der Zähler so gesetzt, dass beim Start nur ein Fehler auftreten darf
  Temperatursensor_Fehler_Zaehler = Temperatursensor_Fehler_Zaehler_Speicher - 1;           //Hier wird der Zähler so gesetzt, dass beim Start nur ein Fehler auftreten darf
  AnalogSensorFehler_Zaehler = AnalogSensorFehler_Zaehler_Speicher - 1;           //Hier wird der Zähler so gesetzt, dass beim Start nur ein Fehler auftreten darf

  Lampentest();
  Bremse_Auslesen();
  Zuendung_auslesen();
  Sport_Modus_auslesen();
  AnalogSensor_Fehler();
  Gaspedal_check();
  Temperatur_start();
  /*SoftSerial.begin(9600);   //Kommunikation mit Leistungselektronik PA15&PB3
    SoftSerial.write((byte)0xE1);   //UART Mode
    SoftSerial.write((byte)0x8A);   //Direction
    SoftSerial.write((byte)0x00);   //STOP
    SoftSerial.write((byte)0x82);   //Current Limit
    SoftSerial.write((byte)0xEF);   //239A
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  Zyklische_Aufrufe();

  if (Freigabe || Zuendung && Notbetrieb && !Bremse) {
    pinMode(Enable_Pin, OUTPUT);
    digitalWrite(Enable_Pin, LOW);
    //SoftSerial.write((byte)0x8A);    //Direction
    //SoftSerial.write((byte)0x01);    // FORWARD
    Gaspedal(); //Verändert Sollwert abhängig vom Pedal
  }
  else if (Freigabe || Zuendung && Notbetrieb && Bremse && Regenerativbremsen) {
    pinMode(Enable_Pin, OUTPUT);
    digitalWrite(Enable_Pin, LOW);
    //SoftSerial.write((byte)0x8A);    //Direction
    //  SoftSerial.write((byte)0x02);    // REGEN
  }
  else {
    pinMode(Enable_Pin, INPUT);
    //SoftSerial.write((byte)0x8A);    //Direction
    //SoftSerial.write((byte)0x00);    // STOP
  }
}
