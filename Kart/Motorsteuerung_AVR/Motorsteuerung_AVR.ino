//Board: Arduino Mega

//DIP Schalter Leistungselektronik
//1 OFF
//2 OFF
//3 OFF   Peak-Current off, sonst Drehen die Reifen unkontrollierbar durch
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
#include <Adafruit_GFX.h>
#include <Fonts/myownfont.h>
#include <Adafruit_SSD1306.h>

//##############################################################################
//####I2C Adressen & AnalogSensor
//I2C Pins: 20 (SDA), 21 (SCL) //für den Display und analog Sensor interessant
#define I2C_ADDRESS 0x48    //Adresse für den AnalogSensor
//##############################################################################
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

//###Pin Zuweisungen
//Verfügbar: 2
#define Notbetrieb_PIN 28        //Schalter Notbetrieb
#define Bremse_PIN 3
#define Sportmodus_PIN 22
#define ONE_WIRE_BUS 44
#define Uebertemperatur_PIN_Leuchte 46
#define Sport_Modus_PIN_Leuchte 51
#define Regenerativbremsen_PIN 31
#define Regenerativbremsen_PIN_Leuchte 48
#define Notbetrieb_PIN_Leuchte 50
#define Freigabe_PIN_Leuchte 49
#define Gaspedal_check_PIN 19
#define TestLED_PIN 13
//##############################################################################
//###Maximal- und Minimalwerte für Temperaturen, nicht verändern
#define MAX_TEMP_AKKU_STARTUP 45
#define MAX_TEMP_AKKU_RUN 50
#define MAX_TEMP_MOTOR 110
#define MIN_TEMP_AKKU 10
//##############################################################################
//###Maximalwer Strom, interessant für Den Betriebsmodi, wird per TX/RX übertragen
#define MAX_VALUE_CURRENT_SPORT 200
#define MAX_VALUE_CURRENT_LOW 20
#define MAX_VALUE_CURRENT_NOTBETRIEB 50   //hier Strom eintragen <------------------------------------------------------------------------------------------------------
#define Regen_on 60  //Ampere
#define Regen_on_Sport 80  //Ampere
#define Regen_off  20   //Mindestens 10A, da sonst der Motor nicht stoppt
//##############################################################################
//GASPEDAL gemessene Spannungen
int GASPEDAL_MAX = 4500;  //Maximalwert der vom Gaspedal erreicht werden kann <-----------------------------------------------------------------------------------------
int GASPEDAL_MIN = 937; //Offset Spannung Gaspedal in mV  <-------------------------------------------------------------------------------------------------------------
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
volatile bool Sport_Modus = false;
volatile bool Notbetrieb = false;
volatile bool Notbetrieb_alt = false;
volatile bool Gaspedal_angeschlossen = false;
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
int Strom_regen_hex = 0x00;

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
const int interval_Temperatur = 2048;  //Wichtig für die Temp Messung
unsigned long int previousMillis_Temperatur = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_OLED = 1024;  //Wichtig für den OLED 1000 ist auch gut
unsigned long int previousMillis_OLED = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_Batteriespannung = 2000;  //Wichtig für die Batteriespannung
unsigned long int previousMillis_Batteriespannung = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_LED = 256;  //Wichtig für die Batteriespannung
unsigned long int previousMillis_LED = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_Schalter = 512;  //Wichtig für die Batteriespannung
unsigned long int previousMillis_Schalter = 0; //speichert den Zeitpunkt des letzten durchgehens

const unsigned int Interval_auslesen = 256;
unsigned long int Interval_auslesen_verstrichen = 0;
const unsigned int Interval_Temperatur = 2500;
unsigned long int Interval_Temperatur_verstrichen = 0;
unsigned long int measureTime = 0;


int State = 0; //0 = Stopp, 1 = Notbetrieb&&Zündung, 2 = OK,  3 = OK, Bremse aktiv
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

ADS1115_WE adc(I2C_ADDRESS);



void setup() {
  Serial.begin(9600);  //Kommunikation mit Leistungselektronik
  Serial.write(byte(0xE0));   //UART Mode, wenn 3 Sekunden kein Update erfolgt, Shutdown!
  Serial.write(byte(0x8A));    //Direction
  Serial.write(byte(0x00));    // STOP
  Serial.write(byte(0x84)); //accel limit
  Serial.write(byte(0x00)); //min
  Serial.write(byte(0x85)); //decel limit
  Serial.write(byte(0x00)); //min

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  pinMode(Sport_Modus_PIN_Leuchte, OUTPUT);
  pinMode(Notbetrieb_PIN_Leuchte, OUTPUT);
  pinMode(Regenerativbremsen_PIN_Leuchte, OUTPUT);  //Lampe für Regenerativbremsen ansprechen
  pinMode(Uebertemperatur_PIN_Leuchte, OUTPUT);
  pinMode(Freigabe_PIN_Leuchte, OUTPUT);
  pinMode(TestLED_PIN, OUTPUT);
  pinMode(Bremse_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(Bremse_PIN), Bremse_Auslesen, CHANGE); //Interrupt an den BREMSE_PIN
  pinMode(Sportmodus_PIN, INPUT_PULLUP);
  pinMode(Notbetrieb_PIN, INPUT_PULLUP);
  pinMode(Gaspedal_check_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Gaspedal_check_PIN), Gaspedal_check, CHANGE);
  pinMode(Regenerativbremsen_PIN, INPUT_PULLUP);

  Lampentest();

  adc.init();
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);   //maximal 5000 mV
  adc.setConvRate(ADS1115_860_SPS);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc.setMeasureMode(ADS1115_SINGLE);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);

  Bremse_Auslesen();
  AnalogSensor_Fehler();
  Gaspedal_check();

  Temperatur_start();

  OLED_Display();
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  Zyklische_Aufrufe();



  int State_alt = State;

  if (!Gaspedal_angeschlossen || AnalogSensorFehler) {    //hier muss der Motor stehen bleiben, da das Gaspedal oder Sensor Fehler melden
    State = 0;
  }
  else if (Notbetrieb && !AnalogSensorFehler && Gaspedal_angeschlossen) {  //Gaspedal und Analogsensor ok, Notbetrieb eingeschaltet
    State = 1;
  }
  else if (Freigabe) {
    State = 2;
  }
  else {
    State = 0;
  }


  if (State_alt != State) {
    switch (State) {  // 1 = Notbetrieb&&keine kritischen Fehler , 2 = OK
      case 0:             //0 = Stopp oder kritischer Fehler
        Serial.write(byte(0x8A));    //Direction
        Serial.write(byte(0x00));    // STOP
        Serial.write(byte(0x80));    //Speed
        Serial.write(byte(0x00));    // STOP
        break;
      case 1:         // Notbetrieb&&Zündung
        Serial.write(byte(0x8A));    //Direction
        Serial.write(byte(0x01));    // FORWARD
        break;
      case 2:       //Alles OK
        Serial.write(byte(0x8A));    //Direction
        Serial.write(byte(0x01));    // FORWARD
        break;
      default: State = 0;
        break;
    }
  }
  if (State == 1 || State == 2) {
    Gaspedal(); //Verändert Sollwert abhängig vom Pedal
  }
  else {
    Serial.write(byte(0x8A));    //Direction
    Serial.write(byte(0x00));    // STOP
    Serial.write(byte(0x80));    //Speed
    Serial.write(byte(0x00));    // STOP
  }
}
