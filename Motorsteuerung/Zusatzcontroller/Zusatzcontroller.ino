#define Drehzahl_Sensor 2  //Interruptfähig, für die Drehzahl berechnung notwendig


volatile uint32_t rev; // Revolution Count
float Reifen_Durchmesser = 0.265; //in Meter
float ReifenxPI = 0.0;
float MinimaleGeschwindigkeit = 0.5; //in Meter pro Sekunde
int Geschwindigkeit_in_kmh = 0;

unsigned long int currentMillis = 0;
unsigned int Abtastintervall = 0;  //Wichtig für die Drehzahl berechnung, kann 0 bleiben da es in der Setup Funktion berechnet wird
unsigned long int previousMillis_Abtastintervall = 0; //speichert den Zeitpunkt des letzten durchgehens


void setup() {
  // put your setup code here, to run once:
  pinMode(Drehzahl_Sensor, INPUT);    //Externer Pull-Down muss verdrahtet werden
  attachInterrupt(digitalPinToInterrupt(Induktiver_Sensor), eineUmdrehung, RISING); //Interrupt am Induktiven Sensor

  ReifenxPI = Reifen_Durchmesser * PI;
  Abtastintervall = (Reifen_Durchmesser / MinimaleGeschwindigkeit) * 1000;

}

void loop() {
  // put your main code here, to run repeatedly:

}
