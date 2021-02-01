//https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/esp8266-sensordaten-auf-webseite-ausgeben

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#define Lichtschranke_PIN_1 D1
#define Lichtschranke_PIN_2 D2

#define Faktorµs 1000000

short int addr = 8; //Startwert 

volatile unsigned long int Lichtschranke_1 = 0;
volatile unsigned long int Lichtschranke_2 = 0;

volatile bool Lichtschranke_1_toggle = false;
volatile bool Lichtschranke_2_toggle = false;

double Geschwindigkeit_kmh = 0.0;
double Geschwindigkeit_kmh_1 = 0.0;
double Geschwindigkeit_kmh_2 = 0.0;
double Geschwindigkeit_kmh_3 = 0.0;

double Geschwindigkeit_kmh_max = 0.0;

const double min_Geschwindigkeit 0.3; //in m/s

double max_Zeit = 0;

const double Distanz = 3.0; //Distanz zwischen den Lichtschranken in Metern

/*Put your SSID & Password*/
const char* ssid = "YourNetworkName";  // Enter SSID here
const char* password = "YourPassword";  //Enter Password here

ESP8266WebServer server(80);

void setup() {
  EEPROM.begin(512);
  if (EEPROM.read(0) == 0b11111111 && EEPROM.read(7) == 0b11111111){  //nichts steht im Speicher
    EEPROM.put(0,0.0);
  }
  Geschwindigkeit_kmh_max = EEPROM.get(0); //an dieser Stelle ist die maximale Geschwindigkeit gespeichert
  
  
  pinMode (Lichtschranke_PIN_1, INPUT);
  pinMode (Lichtschranke_PIN_2, INPUT);
  attachInterrupt(digitalPinToInterrupt(Lichtschranke_PIN_1), Schranke_1, RISING);
  attachInterrupt(digitalPinToInterrupt(Lichtschranke_PIN_2), Schranke_2, RISING);
  
  max_Zeit = ((Distanz/min_Geschwindigkeit)*Faktorµs);    //wenn diese Zeit überschritten wird
  
  Serial.begin(115200);
  delay(100);
  
  pinMode(Lichtschranke_PIN_1, INPUT);
  pinMode(Lichtschranke_PIN_1, INPUT);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: "); 
  Serial.println(WiFi.localIP());

  server.on("/reset", handle_reset);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  
  server.handleClient();
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  
}

void handle_reset() {
  Geschwindigkeit_kmh_max = 0.0;
   EEPROM.put(0,Geschwindigkeit_kmh_max);
  Lichtschranke_1_toggle = false;
  Lichtschranke_2_toggle = false;
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

void Schranke_1 () {
  if (!Lichtschranke_1_toggle){
  Lichtschranke_1 = micros();
  Lichtschranke_1_toggle = true;
}
}

void Schranke_2 () {
  if (!Lichtschranke_2_toggle){
  Lichtschranke_2 = micros();
  Lichtschranke_2_toggle = true;
}
}

void Geschwindigkeit () {
  int Differenz = (Lichtschranke_1-Lichtschranke_2);
  Differenz = abs(Differenz);
  
  if (Differenz >= max_Zeit) {  //wenn diese Bedingung erfüllt ist, war die Zeit zwischen dem Bestätigen der Lichtschranke zu lang
    Lichtschranke_1_toggle = false;
    Lichtschranke_2_toggle = false;
  }
  
  if (Lichtschranke_1_toggle && Lichtschranke_2_toggle){
  Geschwindigkeit_ms = Distanz / ((Lichtschranke_1-Lichtschranke_2)/Faktorµs);
  Geschwindigkeit_kmh = Geschwindigkeit_ms *3.6;
  
  EEPROM.put(addr, Geschwindigkeit_kmh); //schreibe Messwert in den Speicher
   // advance to the next address.  there are 512 bytes in
  // the EEPROM, so go back to 8 when we hit 504.
  // save all changes to the flash.
  addr += sizeof(double); //Move address to the next byte
  if (addr >= 504) {
    addr = 8;
  }
  
  if (Geschwindigkeit_kmh > Geschwindigkeit_kmh_max) {
    Geschwindigkeit_kmh_max = Geschwindigkeit_kmh;
   EEPROM.put(0, Geschwindigkeit_kmh_max);  //Maximale Geschwindigkeit wird in Byte 00...07 gespeichert
  }
  
  
Lichtschranke_1_toggle = false;
Lichtschranke_2_toggle = false;
  }
}