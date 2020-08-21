enum State_enum {Zaehler_erhoehen, PWM_einschalten, Messen_1, Messen_2, PWM_ausschalten, Pin_wechseln, Fertig};

int PWMPin = 3;     //Pin an welchen der Transistor angeschlossen wird, welcher die Spule schaltet Pin 3=480Hz und Pin 5=980Hz
int analogPin = A0;   //Der erste Analoge Pin wird verwendet die Spannung des Kondensators zu messen
int analogWert = 0;   //dieser Wert wird nachher überschrieben. Der sicherheit
int analogGrenzWert = 5;  //in etwa 24 Millivolt, also vernachlässigbar! Um Probleme durch ein Rauschen zu vermeiden ungleich 0.
int PWM = 0;      //Startwert der Pulsweite
unsigned long current = 0;    //in dieser Variablen wir die aktuelle Zeit gespeichert
unsigned long intervall = 0;    //hier wird der Zeitpunkt gespeichert, ab welchem die Pulsweite gestartet wurde
unsigned long intervall1 = 3000;  //3 Sekunden
unsigned long intervall2 = 10000; //10 Sekunden
uint8_t state  = Zaehler_erhoehen;    //Startwert. Um immer mit gleichen Bedingungen zu starten

void setup() {
  Serial.begin(9600);     //Es wird eine Serielle Kommunikation eingerichtet, welche eine Baudrate von 9600 hat
  pinMode(PWMPin, OUTPUT);    //Pin als AusgangsPin deklarieren, kann später durchs Programm geändert weren
  Serial.println("Durchlauf starten");  //Hilfreich um den Anfang zu finden
}

void loop() {
  current = millis();       //Dauerschleife

  switch (state)        //Switch Anweisung welche die Zustände abarbeitet
  {
    case Zaehler_erhoehen:          //Zustand Zähler erhöhen
      if (PWM < 254)        //Die Pulsweite kann nur die Werte 0 bis 255 annehmen, der Minimale sinnvolle Wert ist 1 und der Maximale sinnvolle Wert ist 254
      { PWM++;           //den Zähler um 1 erhöhen
        state = PWM_einschalten;     //in den nächsten Zustand springen
      }
      else
      { state = Pin_wechseln;      //in Pin_wechseln springen
      }
      break;
    case PWM_einschalten:         //Zustand Pulsweitenmodulation
      analogWrite(PWMPin, PWM);     //Den Pin und damit Transitor mit entsprechender Pulsweite versehen
      intervall = current;        //Zeitpunkt speichern, ab welchem die Pulsweiten Modulation gestartet wurde
      state = Messen_1;       //In den Zustand Messen 1 springen
      break;
    case Messen_1:            //Zustand Messen nach 3 Sekunden
      if (current - intervall >= intervall1)  //Wenn 3 Sekunden vergangen sind
      { analogWert = analogRead(analogPin);  //Spannung am Pin Messen
        Serial.println(analogWert);     //Messwert ausgeben
        state = Messen_2;
      }       //In den Zustand Messen 2 springen
      break;
    case Messen_2:            //Zustand Messen 2
      if (current - intervall >= intervall2)  //Wenn 10 Sekunden vergangen sind
      { analogWert = analogRead(analogPin);  //Spannung am Pin Messen
        Serial.println(analogWert);     //Messwert ausgeben
        state = PWM_ausschalten;
      }     //In den Zustand PWM Messen springen
      break;
    case PWM_ausschalten:         //Zustand PWM ausschalten
      analogWrite(PWMPin, 0);       //PWM ausschalten
      state = Zaehler_erhoehen;     //In den Zustand Zaehler_erhoehen springen
      break;
    case Pin_wechseln:          //Zustand Pin_wechseln
      if (PWMPin == 3)
      { pinMode (PWMPin, INPUT);     //alten PWM Pin als Eingang Konfigurieren
        PWMPin = 5;         //auf den Pin 5 wechseln, da dieser eine andere Frequenz hat.
        PWM = 0;          //Pulsweite zurücksetzen
        pinMode(PWMPin, OUTPUT);      //neuen PWM Pin als Ausgang Konfigurieren
        Serial.println("Pin gewechselt (980Hz)");  //Hilfreich bei der Auswertung der Messdaten
        state = Zaehler_erhoehen;     //In den nächsten Zustand springen
      }
      else {
        state = Fertig;         //Wenn bereits alle Messwerte erfasst wurden, in den Endzustand übergehen
      }
      break;
    case Fertig:            //Zustand Fertig
      Serial.println("Durchlauf beendet");   //Hilfreich um das Ende der Messreihe zu erkennen
      delay(10000);         //Serial Monitor offen lassen
      break;
  }
}
