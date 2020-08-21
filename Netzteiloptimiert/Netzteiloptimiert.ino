#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdlib.h>
#define ONE_WIRE_BUS 2      // Data wire is plugged into pin 2 on the Arduino
#define LampeTasterPin 3
#define TasterPin 4
#define LufterPin 5
#define BacklightPin 6
#define NetzteilPin 7
#define AmpelRotPin 13
#define AmpelGelbPin 1
#define AmpelGrunPin 0
#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

static const byte ASCII[][5] = {// ASCII Tabelle mit Fonts
  {0x00, 0x00, 0x00, 0x00, 0x00} // 20
  , {0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
  , {0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
  , {0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
  , {0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
  , {0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
  , {0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
  , {0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
  , {0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
  , {0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
  , {0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
  , {0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
  , {0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
  , {0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
  , {0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
  , {0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
  , {0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
  , {0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
  , {0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
  , {0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
  , {0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
  , {0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
  , {0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
  , {0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
  , {0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
  , {0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
  , {0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
  , {0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
  , {0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
  , {0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
  , {0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
  , {0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
  , {0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
  , {0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
  , {0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
  , {0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
  , {0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
  , {0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
  , {0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
  , {0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
  , {0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
  , {0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
  , {0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
  , {0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
  , {0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
  , {0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
  , {0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
  , {0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
  , {0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
  , {0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
  , {0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
  , {0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
  , {0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
  , {0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
  , {0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
  , {0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
  , {0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
  , {0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
  , {0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
  , {0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
  , {0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
  , {0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
  , {0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
  , {0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
  , {0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
  , {0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
  , {0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
  , {0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
  , {0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
  , {0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
  , {0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
  , {0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
  , {0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
  , {0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
  , {0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
  , {0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
  , {0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
  , {0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
  , {0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
  , {0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
  , {0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
  , {0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
  , {0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
  , {0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
  , {0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
  , {0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
  , {0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
  , {0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
  , {0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
  , {0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
  , {0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
  , {0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
  , {0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
  , {0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
  , {0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
  , {0x78, 0x46, 0x41, 0x46, 0x78} // 7f →
};

void LcdWriteString(char *characters) {
  // String ausgeben
  while (*characters) LcdWriteCharacter(*characters++);
}
void LcdWriteCharacter(char character) {
  // ASCII Zeichen ausgeben aus der Tabelle oben
  for (int i = 0; i < 5; i++) LcdWriteData(ASCII[character - 0x20][i]);
  LcdWriteData(0x00);
}
void LcdWriteCmd(byte cmd) {
  // Kommando an Display senden
  digitalWrite(DC, LOW); //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
  digitalWrite(CE, HIGH);
}
void LcdWriteData(byte cmd) {
  // Daten an Display senden
  digitalWrite(DC, HIGH); //DC pin is high for data
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
  digitalWrite(CE, HIGH);
}
void LcdClearScreen() {
  // Bildschirm leeren
  for (int i = 0; i < 504; i++)
    LcdWriteData(0x00);
}
void LcdXY(int x, int y) {
  // an X / Y Position gehen
  LcdWriteCmd(0x80 | x); // Spalte
  LcdWriteCmd(0x40 | y); // Zeile
}


char string[8];
char Temp;
bool TemperaturinOrdnung = false;
bool TemperaturSensorinOrdnung = false;
bool Taster = false;
bool letzterTasterZustand = false;
bool Einschalten = false;
bool Netzteil = false;
bool ueberhitzt = false;
bool LampeTaster = false;
byte pwmLufter = 255;
short Temperatur = 0;
unsigned long currentMillis = 0; // nicht verändern/ nicht von Interesse
unsigned long previousMillisNetzteil = 0; //nicht verändern/ nicht von Interesse
const long intervalNetzteil = 180000; //Dauer bis das Netzteil erneut eingeschaltet werden darf (3 Minuten)
unsigned long previousMillisLCD = 0;        // will store last time LCD was updated
const long intervalLCD = 1000;           // interval at which to update (milliseconds)
unsigned long previousMillisLED = 0; //nicht verändern/ nicht von Interesse
const long intervalLED = 250; //Dauer bis die LEd erneut eingeschaltet wird




void setup() {
  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(BacklightPin, OUTPUT);
  pinMode(LampeTasterPin, OUTPUT);
  pinMode(TasterPin, INPUT);
  pinMode(LufterPin, OUTPUT);
  pinMode(AmpelRotPin, OUTPUT);
  pinMode(AmpelGelbPin, OUTPUT);
  pinMode(AmpelGrunPin, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);
  analogWrite(BacklightPin, 100);
  LcdWriteCmd(0x21); // LCD extended commands
  LcdWriteCmd(0xB8); // set LCD Vop (contrast)
  LcdWriteCmd(0x04); // set temp coefficent
  LcdWriteCmd(0x14); // LCD bias mode 1:40
  LcdWriteCmd(0x20); // LCD basic commands
  LcdWriteCmd(0x0C); // LCD normal video
  LcdClearScreen();
  sensors.begin();
  //Serial.begin(9600);
  //hier LampenTest und Lüftertest
  analogWrite(LufterPin, 255);
  digitalWrite(LampeTasterPin, HIGH);
  digitalWrite(AmpelRotPin, HIGH);
  digitalWrite(AmpelGelbPin, HIGH);
  digitalWrite(AmpelGrunPin, HIGH);
  delay(3000);
  analogWrite(LufterPin, 0);
  digitalWrite(LampeTasterPin, LOW);
  digitalWrite(AmpelRotPin, LOW);
  digitalWrite(AmpelGelbPin, LOW);
  digitalWrite(AmpelGrunPin, LOW);
}

void LCDaktualisieren () {

  LcdClearScreen();
  LcdXY(0, 0);
  LcdWriteString("Temperatur ist");
  LcdXY(0, 1);
  LcdWriteString(Temp);
  LcdXY(35, 1);
  LcdWriteString("Celsius");

  if (!TemperaturSensorinOrdnung) {
    LcdXY(0, 3);
    LcdWriteString("Fehler");
    LcdXY(0, 4);
    LcdWriteString("Temperatur-");
    LcdXY(0, 5);
    LcdWriteString("sensor");
  }

  if (Temperatur < 40 && TemperaturSensorinOrdnung && !ueberhitzt) {
    LcdXY(0, 2);
    LcdWriteString("Temperatur");
    LcdXY(0, 3);
    LcdWriteString("in Ordung");
    if (!Netzteil) {
      LcdXY(0, 4);
      LcdWriteString("Einschalten");
      LcdXY(0, 5);
      LcdWriteString("moeglich");
    }
    if (Netzteil) {
      LcdXY(0, 4);
      LcdWriteString("Netzteil");
      LcdXY(0, 5);
      LcdWriteString("eingeschaltet");
    }
  }

  if (Temperatur >= 40 && Temperatur < 50 && !ueberhitzt) {
    LcdXY(0, 2);
    LcdWriteString("Temperatur");
    LcdXY(0, 3);
    LcdWriteString("hoch");
    if (!Netzteil) {
      LcdXY(0, 4);
      LcdWriteString("Einschalten");
      LcdXY(0, 5);
      LcdWriteString("moeglich");
    }
    if (Netzteil) {
      LcdXY(0, 4);
      LcdWriteString("Netzteil");
      LcdXY(0, 5);
      LcdWriteString("eingeschaltet");
    }
  }

  if (Temperatur >= 50 && !ueberhitzt) {
    LcdXY(0, 2);
    LcdWriteString("Temperatur");
    LcdXY(0, 3);
    LcdWriteString("sehr hoch");
    if (!Netzteil) {
      LcdXY(0, 4);
      LcdWriteString("Einschalten");
      LcdXY(0, 5);
      LcdWriteString("moeglich");
    }
    if (Netzteil) {
      LcdXY(0, 4);
      LcdWriteString("Netzteil");
      LcdXY(0, 5);
      LcdWriteString("eingeschaltet");
      LcdXY(0, 6);
      LcdWriteString("Last zu hoch");
    }
  }

  if (ueberhitzt) {
    LcdXY(0, 2);
    LcdWriteString("Netzteil ueber-");
    LcdXY(0, 3);
    LcdWriteString("hitzt. Wieder-");
    LcdXY(0, 4);
    LcdWriteString("einschalten in");
    LcdXY(0, 5);
    LcdWriteString("3 Minuten");
  }
}

void BlinkenLampeTaster () {
  //Steuerung der Lampe des Taster
  if (Temperatur >= 50 || ueberhitzt) {

    if (currentMillis - previousMillisLED >= intervalLED) {
      previousMillisLED = currentMillis;
      // if the LED is off turn it on and vice-versa:
      if (!LampeTaster) {
        LampeTaster = true;
      }
      else {
        LampeTaster = false;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(LampeTasterPin , LampeTaster );
    }
  }
}

void Ampel () {
  if (ueberhitzt || !TemperaturSensorinOrdnung) {
    digitalWrite(AmpelRotPin, HIGH);
    digitalWrite(AmpelGelbPin, LOW);
    digitalWrite(AmpelGrunPin, LOW);
  }

  else {
    if (Temperatur <= 30) {
      digitalWrite(AmpelRotPin, LOW);
      digitalWrite(AmpelGelbPin, LOW);
      digitalWrite(AmpelGrunPin, HIGH);
    }

    if (Temperatur < 30 && Temperatur <= 35) {
      digitalWrite(AmpelRotPin, LOW);
      digitalWrite(AmpelGelbPin, HIGH);
      digitalWrite(AmpelGrunPin, HIGH);
    }

    if (Temperatur > 35 && Temperatur <= 40) {
      digitalWrite(AmpelRotPin, LOW);
      digitalWrite(AmpelGelbPin, HIGH);
      digitalWrite(AmpelGrunPin, LOW);
    }

    if (Temperatur > 40 && Temperatur <= 50) {
      digitalWrite(AmpelRotPin, HIGH);
      digitalWrite(AmpelGelbPin, HIGH);
      digitalWrite(AmpelGrunPin, LOW);
    }

    if (Temperatur > 50) {
      digitalWrite(AmpelRotPin, HIGH);
      digitalWrite(AmpelGelbPin, LOW);
      digitalWrite(AmpelGrunPin, LOW);
    }
  }
}

void Lufter () {
  /* pwmLufter = map(Temperatur, 30, 50, 120, 255);
    if (Temperatur <= 30) {
     pwmLufter = 0; //Luefter unter 30C abschalten
    }
    else if (Temperatur >= 50 || ueberhitzt) {
     pwmLufter = 255; //Luefter über 50C voll aufdrehen
    }
    analogWrite (LufterPin, pwmLufter); //Luefter Geschwindigkeit an den Pin schreiben
   
  */
  if (Temperatur >= 50 || ueberhitzt) {
    pwmLufter = 255;
  }
  else {
    pwmLufter = 0;
  }
  analogWrite (LufterPin, pwmLufter);
}


void Tempsensorcheck () {
  if (Temperatur >= 0) {
    TemperaturSensorinOrdnung = true; // hier Temperatur Sensor Abfrage
  }
  else {
    TemperaturSensorinOrdnung = false;
  }
}

void ueberhitzcheck () {
  Tempsensorcheck ();
  if (Temperatur >= 60) {
    ueberhitzt = true; // bei 60C überhitzt das Netzteil
  }
  if (ueberhitzt && Temperatur >= 50 ) {
    previousMillisNetzteil = currentMillis; //Timer zurücksetzten weil Temperatur noch zu hoch
  }
  if (ueberhitzt && currentMillis - previousMillisNetzteil >= intervalNetzteil) {
    ueberhitzt = false; //Wenn die Zeit abgelaufen ist
  }
  if (TemperaturSensorinOrdnung && !ueberhitzt) {
    TemperaturinOrdnung = true;
  }
}


void check () {

  //abfrage des Tasters
  Taster = digitalRead(TasterPin);
  if (Taster && Taster != letzterTasterZustand) {
    Einschalten = !Einschalten;
    return;
  } //Vergleich den letzten Zustand des Tasters mit dem aktuellen Zustand
  else {
    Temp = (char)Temperatur;
    LCDaktualisieren (); // Aktualisiert den LCD Bildschirm
  }

  //abfrage des Tasters
  Taster = digitalRead(TasterPin);
  if (Taster && Taster != letzterTasterZustand) {
    Einschalten = !Einschalten;
    return;
  } //Vergleich den letzten Zustand des Tasters mit dem aktuellen Zustand
  else {
    Ampel ();  //Aktualisiert die Ampel
  }


  //abfrage des Tasters
  Taster = digitalRead(TasterPin);
  if (Taster && Taster != letzterTasterZustand) {
    Einschalten = !Einschalten;
    return;
  } //Vergleich den letzten Zustand des Tasters mit dem aktuellen Zustand
  else {
    Lufter (); //Aktualisiert die Lüfter
  }

  //abfrage des Tasters
  Taster = digitalRead(TasterPin);
  if (Taster && Taster != letzterTasterZustand) {
    Einschalten = !Einschalten;
    return;
  } //Vergleich den letzten Zustand des Tasters mit dem aktuellen Zustand
  else {
    ueberhitzcheck (); //Aktualisiert den Überhitzt Check
  }

  //abfrage des Tasters
  Taster = digitalRead(TasterPin);
  if (Taster && Taster != letzterTasterZustand) {
    Einschalten = !Einschalten;
    return;
  } //Vergleich den letzten Zustand des Tasters mit dem aktuellen Zustand
  else {
    BlinkenLampeTaster (); // Lässt die Lampe des Tasters Blinken
  }
}



void loop() {
  currentMillis = millis();

  //abfrage des Tasters
  Taster = digitalRead(TasterPin);
  if (Taster && Taster != letzterTasterZustand) {
    Einschalten = !Einschalten;
  }
  else {
    sensors.requestTemperatures(); // Send the command to get temperatures
    Temperatur = (int)sensors.getTempCByIndex(0); //Temperatur wird weiter verwendet
    check (); // führt alle anderen Nebenfunktionen aus, wenn in dieser Zeit der Taster gedrückt wird, springt er nach durchlaufen einer Unterfunktion aus der check funktion heraus und schaltet das Netzteil entsprechend
  }


  //Netzteil
  if (Einschalten && TemperaturinOrdnung) {
    Netzteil = true;
    pinMode(NetzteilPin, OUTPUT);
    digitalWrite(NetzteilPin, LOW);
  }
  else {
    pinMode(NetzteilPin, INPUT);
    Netzteil = false;
    Einschalten = false;
  }

  letzterTasterZustand = Taster;  // save the current state as the last state, for next time through the loop

}
