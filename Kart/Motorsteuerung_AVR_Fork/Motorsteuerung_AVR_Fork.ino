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
//#include<Wire.h>
#include <Adafruit_GFX.h>
//#include <Fonts/myownfont.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
//#include <Adafruit_SSD1306.h>

//##############################################################################
//####I2C Adresse
//#define OLED_ADDR   0x3C
//##############################################################################
//#define OLED_ADDR   0x3C
//Adafruit_SSD1306 display(-1);

//Reserve 43
//Reserve 41 grau-pink

//###Pin Zuweisungen
//Verfügbar: 2
#define NUMPIXELS 8
#define NEOPIXEL_PIN    2 //weiße Leitung
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
#define Leistungselektronik_PIN 40 //an Lila anschließen
#define TestLED_PIN 13
#define Rueckwaerts_PIN 18
#define Rueckwaerts_PIN_Leuchte 47
#define Spule_Rueckwaerts 40  //grün-weiß
#define Spule_Vorwaerts 42     //grün-braun
//##############################################################################
//###Maximal- und Minimalwerte für Temperaturen, nicht verändern
#define MAX_TEMP_AKKU_STARTUP 45
#define MAX_TEMP_AKKU_RUN 50
#define MAX_TEMP_MOTOR 70
#define MAX_TEMP_LEISTUNGSELEKTRONIK 60
#define MIN_TEMP_AKKU 5
//##############################################################################
#define GRENZE_GASPEDAL_EMPFINDLICH 30  //0-100%
#define GRENZE_GASPEDAL_EMPFINDLICH_SPORT 10 //0-100%

#define MAX_ACC_DELAY 20//0-100%
#define MIN_ACC_DELAY 2  //0-100%-< so viel Delay nach überschreiten des Wertes "GRENZE_GASPEDAL_EMPFINDLICH"

#define MAX_ACC_DELAY_SPORT 5 //0-100%
#define MIN_ACC_DELAY_SPORT 0 //0-100%-< so viel Delay nach überschreiten des Wertes "GRENZE_GASPEDAL_EMPFINDLICH"

#define MAX_DECC_DELAY 10 //0-100%-< so viel Delay beim wenn das Gaspedal minimal eingedrückt ist
#define MIN_DECC_DELAY 0 //0-100%-< so viel Delay beim Bremsen bleibt nach überschreiten des Wertes "GRENZE_GASPEDAL_EMPFINDLICH"

#define MAX_DECC_DELAY_SPORT 2//0-100%-< so viel Delay beim wenn das Gaspedal minimal eingedrückt ist
#define MIN_DECC_DELAY_SPORT 0 //0-100%-< so viel Delay beim Bremsen bleibt nach überschreiten des Wertes "GRENZE_GASPEDAL_EMPFINDLICH"

#define SPEED 128 //Speed
#define STOP 0 //STOPP
#define FWD 1 //Vorwärts
#define CURR 130
#define REGEN 131 //Regen Limit
#define ACC 132 //Acceleration limit
#define DECC 133 //Decceleration limit
#define OFF_LOW 134
#define ON_LOW 135
#define OFF_HIGH 136
#define ON_HIGH 137
#define DIR 138//Direction
#define VOLT 204 //Versorgungspannung lesen
#define UART 224 //UART Mode
//##############################################################################
//###Maximalwer Strom, interessant für die Betriebsmodi, wird per TX/RX übertragen
#define MAX_VALUE_CURRENT_SPORT 300 //Ampere
#define MAX_VALUE_CURRENT_LOW 80 //Ampere
#define MAX_VALUE_CURRENT_NOTBETRIEB 300 //Ampere
#define MAX_VALUE_CURRENT_RUECKWAERTS 40//Ampere
#define Regen_on 125  //Ampere
#define Regen_on_Sport 125  //Ampere
#define Regen_off  70//Mindestens 10A, da sonst der Motor nicht stoppt
//##############################################################################
//GASPEDAL gemessene Spannungen
#define GASPEDAL_MAX 800  //Maximalwert der vom Gaspedal erreicht werden kann
#define GASPEDAL_MIN 230 //Offset Spannung Gaspedal in 1/1023
//##############################################################################
//###Auflistung und Zuweisung aller verwendeten Sensoren
uint8_t Temperatursensor_Akku_1[8] = {0x28, 0xE2, 0x7B, 0x79, 0xA2, 0x00, 0x03, 0x24};
uint8_t Temperatursensor_Akku_2[8] = {0x28, 0x8A, 0x63, 0x79, 0xA2, 0x00, 0x03, 0x04};
uint8_t Temperatursensor_Akku_3[8] = {0x28, 0x8E, 0x62, 0x79, 0xA2, 0x00, 0x03, 0x15};
uint8_t Temperatursensor_Akku_4[8] = {0x28, 0xA9, 0xE9, 0x79, 0xA2, 0x00, 0x03, 0x9D};
uint8_t Temperatursensor_Akku_5[8] = {0x28, 0x45, 0xB5, 0x79, 0xA2, 0x00, 0x03, 0x7D};
uint8_t Temperatursensor_Motor[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t Temperatursensor_Leistungselektronik [8] = { 0x28, 0xCE, 0x06, 0x45, 0x92, 0x16, 0x02, 0xF2 };
//##############################################################################
//###Auflistung und Zuweisung der Zustände
volatile bool Bremse = true;
volatile bool Gaspedal_angeschlossen = false;
bool Sport_Modus = false;
bool Sportmodus_state_alt = true;
bool Notbetrieb = false;
bool Notbetrieb_alt = true;
bool Rueckwaertsgang = false;
bool Rueckwaertsgang_alt = false;
bool Gang_wechseln = false;
bool Neutral = true;
bool Gang_wechseln_delay = false; //erzeugt einen kleinen Delay bevor der Gang gewechselt wird
bool Uebertemperatur = true;
bool Untertemperatur = false;
bool Temperatursensor_Fehler = true;
bool Freigabe = false;
bool Temperatur_LED_Zustand = false;
bool Temperatursensor_Fehler_LED_Zustand = false;
bool TestLED = false;
bool Regenerativbremsen = false;
bool Leistungselektronik_start = true;    //wird von dem DigitalPin auf true gesetzt und von der Funktion zurückgesetzt
bool Leistungselektronik_check = false;   //wird genutzt um Rechenleistung zu sparen
bool Leistungselektronik = false;
bool Rueckwaerts_LED = false;
bool Inaktiv = false;
//##############################################################################
int Temperatur_Akku_1 = 0;
int Temperatur_Akku_2 = 0;
int Temperatur_Akku_3 = 0;
int Temperatur_Akku_4 = 0;
int Temperatur_Akku_5 = 0;
int Temperatur_Akku_6 = 0;
int Temperatur_Akku_Max = 0;
int Temperatur_Akku_Min = 0;
int Temperatur_Motor = 20;
int Temperatur_Leistungselektronik = 0;
int Temperatur_Leistungselektronik_Max = 0;
int Temperatur_Leistungselektronik_Min = 0;
unsigned short int Temperaturzaehler = 0;

unsigned short int Sollwert_analog = 0;
unsigned short int Sollwert = 0;

int Grenze_Gaspedal_empfindlich = 0;

int Max_Acc_Delay = 0;
int Min_Acc_Delay = 0;
int Max_Decc_Delay = 0;
int Min_Decc_Delay = 0;


int Beschleunigungslimit = 0;
int Beschleunigungslimit_alt = 0;
int Verzoegerungslimit = 0;
int Sollwert_acc = 0;
int Verzoegerungslimit_alt = 0;

int Strom = 0;
int Strom_regen = 0;
int Strom_Rueckwaerts = 0;

int Batteriespannung = 0;
int SOC = 0;

int Leistung = 0;
unsigned short int Rueckwaerts_Zaehler = 0;

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
const unsigned int interval_Schalter = 512;  //Wichtig für die Schalter
unsigned long int previousMillis_Schalter = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_Leistungselektronik = 3000;  //Wichtig für die Schalter
unsigned long int previousMillis_Leistungselektronik = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_Rueckwaerts_LED_LED = 512;  //Wichtig für die LED Rückwärtsgang
unsigned long int previousMillis_Rueckwaerts_LED = 0; //speichert den Zeitpunkt des letzten durchgehens
const unsigned int interval_Inaktiv = 60000;  //Wichtig für das abschalten des großen Relais
unsigned long int previousMillis_Inaktiv = 0; //speichert den Zeitpunkt des letzten durchgehens

const unsigned int interval_Rueckwaerts = 100;  //Der Rueckwärts Knopf muss 1 Sekunde bzw. 4 Durchgänge am Stück gedrückt bleiben
unsigned long int previousMillis_Rueckwaerts = 0; //speichert den Zeitpunkt des letzten durchgehens

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
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  Serial.begin(9600);  //Kommunikation mit Leistungselektronik
  Serial.setTimeout(250);
  SEND(UART, 0);
  SEND(DIR, STOP);
  SEND(SPEED, STOP);
  SEND(ACC, 0);
  SEND(DECC, 0);
  //pixels.begin();
  //pixels.clear();
  //pixels.show();   // Send the updated pixel colors to the hardware.
  //Wire.begin();
  //display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  //display.clearDisplay();
  //display.display();


  pinMode(Sport_Modus_PIN_Leuchte, OUTPUT);
  pinMode(Notbetrieb_PIN_Leuchte, OUTPUT);
  pinMode(Regenerativbremsen_PIN_Leuchte, OUTPUT);  //Lampe für Regenerativbremsen ansprechen
  pinMode(Uebertemperatur_PIN_Leuchte, OUTPUT);
  pinMode(Freigabe_PIN_Leuchte, OUTPUT);
  pinMode(TestLED_PIN, OUTPUT);
  pinMode(Bremse_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Bremse_PIN), Bremse_Auslesen, CHANGE); //Interrupt an den BREMSE_PIN
  pinMode(Sportmodus_PIN, INPUT_PULLUP);
  pinMode(Notbetrieb_PIN, INPUT_PULLUP);
  pinMode(Gaspedal_check_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Gaspedal_check_PIN), Gaspedal_check, CHANGE);
  pinMode(Regenerativbremsen_PIN, INPUT_PULLUP);
  pinMode(Leistungselektronik_PIN, INPUT_PULLUP);   //wird vom Optokoppler auf Masse gezogen
  pinMode(Rueckwaerts_PIN, INPUT_PULLUP);
  pinMode(Rueckwaerts_PIN_Leuchte, OUTPUT);
  pinMode(Spule_Rueckwaerts, OUTPUT);
  digitalWrite(Spule_Rueckwaerts, LOW);
  pinMode(Spule_Vorwaerts, OUTPUT);
  digitalWrite(Spule_Vorwaerts, LOW);

  Lampentest();

  Bremse_Auslesen();
  Gaspedal_check();
  Temperatur_start();
  // OLED_Display();
  Initialwerte_schreiben();
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  Zyklische_Aufrufe();

  int State_alt = State;

  if (!Gaspedal_angeschlossen) {    //hier muss der Motor stehen bleiben, da das Gaspedal einen Fehler meldet
    State = 0;
  }
  else if (!Notbetrieb && !Freigabe) {
    State = 0;
  }
  else if (Notbetrieb && Gaspedal_angeschlossen) {  //Gaspedal, Notbetrieb eingeschaltet
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
        SEND(DIR, STOP);
        SEND(SPEED, STOP);
        Neutral = true;
        Gang_wechseln = true;
        break;
      case 1:         // Notbetrieb && Sensoren ok
        SEND(DIR, FWD);
        break;
      case 2:       //Alles OK
        SEND(DIR, FWD);
        break;
      default: State = 0;
        break;
    }
  }
  if (State == 1 || State == 2) {
    Gaspedal(); //Verändert Sollwert abhängig vom Pedal
  }
}
