#define PRESSED LOW
#define NOT_PRESSED HIGH

int analogPin = A0;

int val = 0;  // variable to store the value read
double val2 = 0; //speichert die Spannung
double val3 = 21.6461495; //double Faktor 
double R = 0.0; //Ohm
double R_temp = 0.0; //Vorauswahl
double R_real = 0.0;
double R_0k85 = 0.85;
double R_1 = 1.0;
double R_1k2 = 1.2;
double R_1k5 = 1.85;    //gemessen
double R_2 = 2.1314;      //gemessen
double R_3 = 3.1499;      //gemessen
double R_6 = 6.222;      //gemessen
double R_12 = 12.0;
double R_18 = 18.0;
double R_24 = 24.0;
int S = 0;
double Entladeschluss = 2.5;

double I = 0;    //Ampere
double Im = 0;    //mAmpere
double mAh = 0;    //mah
double mWh = 0; //  mWh
unsigned long zeit;
unsigned long zeit2;
double Entladeschlussspannung = 0;
int Entladen = 0;   //Entladen 0: Noch nicht gestartet, Entladen 1: Entladen läuft, Entladen 2: Entladen abgeschlossen

unsigned long previousMillis = 0; //nicht verändern/ nicht von Interesse
const short interval = 3000; //alle 3 Sekunden
unsigned long previousMillis2 = 0; //nicht verändern/ nicht von Interesse
const short interval2 = 3000; //alle 3 Sekunden Ausgabe der mWh
int Zaehler = 0;
int Zustand = 0;

const unsigned long shortPress = 100;
const unsigned long  longPress = 1000;

typedef struct Buttons {
  const byte pin = A2;
  const int debounce = 10;

  unsigned long counter = 0;
  bool prevState = NOT_PRESSED;
  bool currentState;
} Button;

Button button;




void setup() {
  Serial.begin(9600);           //  setup Serial
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(button.pin, INPUT_PULLUP);

}


void loop() {
  zeit = millis();
  if (R == 0.0) {
    val = analogRead(analogPin);
    val2 = val / val3;
    Serial.print("Spannung: ");
    Serial.print(val2);
    Serial.println(" Volt");

    if (val2 > 3.0 && val2 < 6.0) {
      S = 1;
      Entladeschlussspannung = Entladeschluss * S;
      Serial.println("1S Erkannt!");
      Serial.print("Entladeschlussspannung: ");
      Serial.print(Entladeschlussspannung);
      Serial.println(" Volt");
      Serial.println("1,5 Ohm verfügbar");
      Serial.println("2 Ohm verfügbar");
      Serial.println("3 Ohm verfügbar");
      Serial.println("6 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 1.5;
      Zustand = 0;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //---------------------------------------------
    if (val2 >= 6.0 && val2 < 8.8) {
      S = 2;
      Entladeschlussspannung = Entladeschluss * S;
      Serial.println("2S Erkannt!");
      Serial.print("Entladeschlussspannung: ");
      Serial.print(Entladeschlussspannung);
      Serial.println(" Volt");
      Serial.println("0,85 Ohm verfügbar");
      Serial.println("1 Ohm verfügbar");
      Serial.println("1,2 Ohm verfügbar");
      Serial.println("1,5 Ohm verfügbar");
      Serial.println("2 Ohm verfügbar");
      Serial.println("3 Ohm verfügbar");
      Serial.println("6 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 0.85;
      Zustand = 1;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //---------------------------------------------
    if (val2 >= 8.8 && val2 < 13.0) {
      S = 3;
      Entladeschlussspannung = Entladeschluss * S;
      Serial.println("3S Erkannt!");
      Serial.print("Entladeschlussspannung: ");
      Serial.print(Entladeschlussspannung);
      Serial.println(" Volt");
      Serial.println("1 Ohm verfügbar");
      Serial.println("1,2 Ohm verfügbar");
      Serial.println("1,5 Ohm verfügbar");
      Serial.println("2 Ohm verfügbar");
      Serial.println("3 Ohm verfügbar");
      Serial.println("6 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 1;
      Zustand = 2;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //----------------------------------------------
    if (val2 >= 13.0 && val2 < 17.0) {
      S = 4;
      Entladeschlussspannung = Entladeschluss * S;
      Serial.println("4S Erkannt!");
      Serial.print("Entladeschlussspannung: ");
      Serial.print(Entladeschlussspannung);
      Serial.println(" Volt");
      Serial.println("1 Ohm verfügbar");
      Serial.println("1,2 Ohm verfügbar");
      Serial.println("1,5 Ohm verfügbar");
      Serial.println("2 Ohm verfügbar");
      Serial.println("3 Ohm verfügbar");
      Serial.println("6 Ohm verfügbar");
      Serial.println("12 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 1;
      Zustand = 3;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //----------------------------------------------
    if (val2 >= 17.0 && val2 < 22.0) {
      S = 5;
      Entladeschlussspannung = Entladeschluss * S;
      Serial.println("5S Erkannt!");
      Serial.print("Entladeschlussspannung: ");
      Serial.print(Entladeschlussspannung);
      Serial.println(" Volt");
      Serial.println("3 Ohm verfügbar");
      Serial.println("6 Ohm verfügbar");
      Serial.println("12 Ohm verfügbar");
      Serial.println("18 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 3.0;
      Zustand = 4;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //----------------------------------------------
    if (val2 >= 22.0 && val2 < 26.0) {
      S = 6;
      Entladeschlussspannung = Entladeschluss * S;
      Serial.println("6S Erkannt!");
      Serial.print("Entladeschlussspannung: ");
      Serial.print(Entladeschlussspannung);
      Serial.println(" Volt");
      Serial.println("3 Ohm verfügbar");
      Serial.println("6 Ohm verfügbar");
      Serial.println("12 Ohm verfügbar");
      Serial.println("18 Ohm verfügbar");
      Serial.println("24 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 3;
      Zustand = 5;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //----------------------------------------------
    if (val2 >= 26.0 && val2 < 30.0) {
      S = 7;
      Entladeschlussspannung = Entladeschluss * S;
      Serial.println("7S Erkannt!");
      Serial.print("Entladeschlussspannung: ");
      Serial.print(Entladeschlussspannung);
      Serial.println(" Volt");
      Serial.println("6 Ohm verfügbar");
      Serial.println("12 Ohm verfügbar");
      Serial.println("18 Ohm verfügbar");
      Serial.println("24 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 6;
      Zustand = 6;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //----------------------------------------------
    if (val2 >= 30.0 && val2 < 34.0) {
      S = 8;
      Entladeschlussspannung = Entladeschluss * S;
      Serial.println("8S Erkannt!");
      Serial.print("Entladeschlussspannung: ");
      Serial.print(Entladeschlussspannung);
      Serial.println(" Volt");
      Serial.println("12 Ohm verfügbar");
      Serial.println("18 Ohm verfügbar");
      Serial.println("24 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 12;
      Zustand = 7;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //----------------------------------------------
    if (val2 >= 34.0 && val2 < 38.0) {
      S = 9;
      Entladeschlussspannung = Entladeschluss * S;
      Serial.println("9S Erkannt!");
      Serial.print("Entladeschlussspannung: ");
      Serial.print(Entladeschlussspannung);
      Serial.println(" Volt");
      Serial.println("12 Ohm verfügbar");
      Serial.println("18 Ohm verfügbar");
      Serial.println("24 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 12;
      Zustand = 8;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //----------------------------------------------
    if (val2 >= 38.0 && val2 < 40.0) {
      Entladeschlussspannung = 38.0;
      Serial.println("9S+ Erkannt!");
      Serial.println("Entladeschlussspannung: 38.0 Volt");
      Serial.println("12 Ohm verfügbar");
      Serial.println("18 Ohm verfügbar");
      Serial.println("24 Ohm verfügbar");
      Serial.println("Kurz drücken um Widerstand zu verändern");
      Serial.println("Lang drücken um Widerstand auszuwählen");
      R_temp = 12;
      Zustand = 9;
      Serial.print(R_temp);
      Serial.println(" Ohm ausgewählt");
      while (R == 0.0) {
        Knopf();
      }
      Serial.print(R);
      Serial.println(" Ohm ausgewählt! Entladen des Akkus beginnt.");
      Widerstand_Real();
      Entladen_starten ();
      Entladen = 1;
    }
    //----------------------------------------------
  } //ende if-Anweisung


  switch (Entladen) {
    case 0:
      break;
    case 1:
      val = analogRead(analogPin);
      val2 = val / val3;
      if (zeit - previousMillis >= interval) {
        previousMillis = zeit;
        Berechnungen();
        Serial.print("Energie: ");
        Serial.print(mWh);
        Serial.println ( "mWh");
        Serial.print("Spannung: ");
        Serial.print(val2);
        Serial.println(" Volt");
        Serial.print("Strom: ");
        Serial.print(Im);
        Serial.println(" Milliampere");
      }
      Knopf();
      if (val2 < Entladeschlussspannung) {
        Entladen = 2;
        Serial.print("Spannung: ");
        Serial.print(val2);
        Serial.println(" Volt");
        Serial.println("Entladen abgeschlossen");
      }
      break;
    case 2:
      Entladen_stoppen();
      Serial.print(mWh);
      Serial.println ( "mWh");
      double a = S * 3.7;
      a = mWh / a;
      Serial.print(a);
      Serial.println(" Milliamperesunden äquivalent"); //hier Miliamperestunden äquivalent
      Entladen = 3;
      break;

    case 3:
      Serial.println("Entladen abgeschlossen, reset um neu zustarten");
      delay(60000);
      break;
  }

}// Ende Loop

void Widerstand_Real () {
  if (R == 0.85) {
    R_real = R_0k85;
  }
  if (R == 1) {
    R_real = R_1;
  }
  if (R == 1.2) {
    R_real = R_1k2;
  }
  else if (R == 1.5) {
    R_real = R_1k5;
  }
  else if (R == 2.0) {
    R_real = R_2;
  }
  else if (R == 3.0) {
    R_real = R_3;
  }
  else if (R == 6.0) {
    R_real = R_6;
  }
  else if (R == 12.0) {
    R_real = R_12;
  }
  else if (R == 18.0) {
    R_real = R_18;
  }
  else if (R == 24.0) {
    R_real = R_24;
  }
  Serial.print("Realer Widerstand: ");
  Serial.print(R_real);
  Serial.println(" Ohm");
}

void Entladen_starten () {
  if (R == 0.85) {
    T1_on();
    T2_on();
    T3_on();
    T4_on();
    T6_on();
    T7_on();
    T9_on();
    T10_on();
    T12_on();
    T13_on();
  }
  else if (R == 1) {
    T1_on();
    T2_on();
    T3_on();
    T4_on();
    T6_on();
    T7_on();
    T9_on();
    T10_on();
  }
  else if (R == 1.2) {
    T1_on();
    T2_on();
    T3_on();
    T4_on();
    T6_on();
    T7_on();
  }
  else if (R == 1.5) {
    T1_on();
    T2_on();
    T3_on();
    T4_on();
  }
  else if (R == 2) {
    T2_on();
    T3_on();
    T4_on();
  }
  else if (R == 3) {
    T3_on();
    T4_on();
  }
  else if (R == 6) {
    T4_on();
  }
  else if (R == 12) {
    T5_on();
    T7_on();
  }
  else if (R == 18) {
    T5_on();
    T8_on();
    T10_on();
  }
  else if (R == 24) {
    T5_on();
    T8_on();
    T11_on();
    T13_on();
  }

}
void Entladen_stoppen () {
  T1_off();
  T2_off();
  T3_off();
  T4_off();
  T5_off();
  T6_off();
  T7_off();
  T8_off();
  T9_off();
  T10_off();
  T11_off();
  T12_off();
  T13_off();
}

void Berechnungen() {
  I = val2 / R_real;                 //Strom
  Im = I * 1000;
  mAh = Im / (3600000 / interval);
  mWh = mWh + (mAh * val2); //  mWh
}

void Knopf() {
  // check the button
  button.currentState = digitalRead(button.pin);
  // has it changed?
  if (button.currentState != button.prevState) {
    delay(button.debounce);
    // update status in case of bounce
    button.currentState = digitalRead(button.pin);
    if (button.currentState == PRESSED) {
      // a new press event occured
      // record when button went down
      button.counter = millis();
    }
    if (button.currentState == NOT_PRESSED) {
      unsigned long currentMillis = millis();
      //if ((currentMillis - button.counter >= shortPress) && !(currentMillis - button.counter >= longPress)) {
      if ((currentMillis - button.counter >= shortPress) && !(currentMillis - button.counter >= longPress)) {
        // short press detected.
        handleShortPress();
        if (Entladen == 0) {
          Serial.print(R_temp);
          Serial.println("Ohm ausgewählt");
        }
      }
      if ((currentMillis - button.counter >= longPress)) {
        // the long press was detected
        handleLongPress();
      }
    }
    // used to detect when state changes
    button.prevState = button.currentState;
  }
}

void handleShortPress() {
  if (Entladen == 0) {
    if (Zustand == 0) {
      if (R_temp == 1.5) {
        R_temp = 2.0;
        return;
      }
      if (R_temp == 2.0) {
        R_temp = 3.0;
        return;
      }
      if (R_temp == 3.0) {
        R_temp = 6.0;
        return;
      }
      if (R_temp == 6.0) {
        R_temp = 1.5;
        return;
      }
    }

    if (Zustand == 1) {
      if (R_temp == 0.85) {
        R_temp = 1;
        return;
      }
      if (R_temp == 1) {
        R_temp = 1.2;
        return;
      }
      if (R_temp == 1) {
        R_temp = 1.2;
        return;
      }
      if (R_temp == 1.2) {
        R_temp = 1.5;
        return;
      }
      if (R_temp == 1.5) {
        R_temp = 2.0;
        return;
      }
      if (R_temp == 2.0) {
        R_temp = 3.0;
        return;
      }
      if (R_temp == 3.0) {
        R_temp = 6.0;
        return;
      }
      if (R_temp == 6.0) {
        R_temp = 0.85;
        return;
      }
    }
    if (Zustand == 2) {
      if (R_temp == 1.0) {
        R_temp = 1.2;
        return;
      }
      if (R_temp == 1.2) {
        R_temp = 1.5;
        return;
      }
      if (R_temp == 1.5) {
        R_temp = 2.0;
        return;
      }
      if (R_temp == 2.0) {
        R_temp = 3.0;
        return;
      }
      if (R_temp == 3.0) {
        R_temp = 6.0;
        return;
      }
      if (R_temp == 6.0) {
        R_temp = 1.0;
        return;
      }
    }
    if (Zustand == 3) {
      if (R_temp == 1.0) {
        R_temp = 1.2;
        return;
      }
      if (R_temp == 1.2) {
        R_temp = 1.5;
        return;
      }
      if (R_temp == 1.5) {
        R_temp = 2.0;
        return;
      }
      if (R_temp == 2.0) {
        R_temp = 3.0;
        return;
      }
      if (R_temp == 3.0) {
        R_temp = 6.0;
        return;
      }
      if (R_temp == 6.0) {
        R_temp = 12.0;
        return;
      }
      if (R_temp == 12.0) {
        R_temp = 1.0;
        return;
      }
    }
    if (Zustand == 4) {
      if (R_temp == 3.0) {
        R_temp = 6.0;
        return;
      }
      if (R_temp == 6.0) {
        R_temp = 12.0;
        return;
      }
      if (R_temp == 12.0) {
        R_temp = 18.0;
        return;
      }
      if (R_temp == 18.0) {
        R_temp = 3.0;
        return;
      }
    }
    if (Zustand == 5) {
      if (R_temp == 3.0) {
        R_temp = 6.0;
        return;
      }
      if (R_temp == 6.0) {
        R_temp = 12.0;
        return;
      }
      if (R_temp == 12.0) {
        R_temp = 18.0;
        return;
      }
      if (R_temp == 18.0) {
        R_temp = 3.0;
        return;
      }
    }
    if (Zustand == 6) {
      if (R_temp == 6.0) {
        R_temp = 12.0;
        return;
      }
      if (R_temp == 12.0) {
        R_temp = 18.0;
        return;
      }
      if (R_temp == 18.0) {
        R_temp = 24.0;
        return;
      }
      if (R_temp == 24.0) {
        R_temp = 6.0;
        return;
      }
    }
    if (Zustand == 7 || Zustand == 8 || Zustand == 9) {
      if (R_temp == 12.0) {
        R_temp = 18.0;
        return;
      }
      if (R_temp == 18.0) {
        R_temp = 24.0;
        return;
      }
      if (R_temp == 24.0) {
        R_temp = 12.0;
        return;
      }
    }
  }
}

void handleLongPress() {
  if (Entladen == 0) {
    R = R_temp; //lang
  }

  if (Entladen == 1) {
    Entladen = 2;
    Serial.println("Entladen abgebrochen!");
  }
}







void T1_off() {
  digitalWrite(A1, LOW);
}
void T1_on() {
  digitalWrite(A1, HIGH);
}
void T2_off() {
  digitalWrite(2, LOW);
}
void T2_on() {
  digitalWrite(2, HIGH);
}
void T3_off() {
  digitalWrite(3, LOW);
}
void T3_on() {
  digitalWrite(3, HIGH);
}
void T4_off() {
  digitalWrite(4, LOW);
}
void T4_on() {
  digitalWrite(4, HIGH);
}
void T5_off() {
  digitalWrite(5, LOW);
}
void T5_on() {
  digitalWrite(5, HIGH);
}
void T6_off() {
  digitalWrite(6, LOW );
}
void T6_on() {
  digitalWrite(6, HIGH);
}
void T7_off() {
  digitalWrite(7, LOW);
}
void T7_on() {
  digitalWrite(7, HIGH);
}
void T8_off() {
  digitalWrite(8, LOW);
}
void T8_on() {
  digitalWrite(8, HIGH);
}
void T9_off() {
  digitalWrite(9, LOW);
}
void T9_on() {
  digitalWrite(9, HIGH);
}
void T10_off() {
  digitalWrite(10, LOW);
}
void T10_on() {
  digitalWrite(10, HIGH);
}
void T11_off() {
  digitalWrite(11, LOW);
}
void T11_on() {
  digitalWrite(11, HIGH);
}
void T12_off() {
  digitalWrite(12, LOW);
}
void T12_on() {
  digitalWrite(12, HIGH );
}
void T13_off() {
  digitalWrite(13, LOW);
}
void T13_on() {
  digitalWrite(13, HIGH);
}
