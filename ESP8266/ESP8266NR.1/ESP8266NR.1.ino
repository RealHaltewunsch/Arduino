#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>



ESP8266WebServer server(80);

const char* ssid = "FRITZ!Box 7590 WF";
const char* password = "74734480506879452195";
// following for the name of: http://name_esp.local/
const char* dns_name = "esp8266";

#include <Adafruit_NeoPixel.h>
int NUMPIXELS = 8;




//Pins
int d0 = 16;
int d1 = 5;
int D0_Zustand = 0;
int ZustandD0_temp = 0;


unsigned long currentMillis = 0; // nicht verändern/ nicht von Interesse
unsigned long previousMillis_WiFi = 0; //nicht verändern/ nicht von Interesse
const unsigned short interval_WiFi = 20000; //Dauer bis die WiFi erneut eingeschaltet werden darf 20 Sekunden
unsigned short interval_D0 = 10;
unsigned long previousMillis_D0 = 0;


int brightness_D0 = 0;     // how bright the LED is
int brightness_D0_ist = 0;     // how bright the LED is
int brightness_D0_map = 0; // how bright the LED is in%
int brightness_D0_map_ist = 0;


int brightness_LED = 0;     // how bright the Ring is
int brightness_LED_ist_alt = 0;     // damit es nicht flackert
int brightness_LEDR_ist = 0;     // how bright the Ring is
int brightness_LEDG_ist = 0;     // how bright the Ring is
int brightness_LEDB_ist = 0;     // how bright the Ring is
int brightness_LED_ist = 0;     // how bright the Ring is
int brightness_LED_map = 0; // how bright the Ring is in%
int brightness_LED_map_ist = 0;



// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, d1, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin(); // Initialisierung der NeoPixel
  for (int gg = 0; gg <=  NUMPIXELS; gg++) {
    pixels.setPixelColor(gg, pixels.Color(0, 0, 0)); // color

  }

  pixels.show(); // Durchführen der Pixel-Ansteuerung

  IPAddress ip(192, 168, 178, 220);
  IPAddress gateway(192, 168, 178, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(192, 168, 178, 1);
  WiFi.config(ip, dns, gateway, subnet);
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);



  WiFi.begin(ssid, password);

  //Serial.print("Verbindung wird hergestellt ...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println();

  //Serial.print("Verbunden! IP-Adresse: ");
  //Serial.println(WiFi.localIP());

  if (MDNS.begin(dns_name)) {
    //Serial.println("DNS gestartet, erreichbar unter: ");
    //Serial.println("http://" + String(dns_name) + ".local/");
  }

  server.onNotFound([]() {
    server.send(404, "text/plain", "Link wurde nicht gefunden!");
  });

  server.on("/", []() {
    server.send(200, "text/plain", "ESP-Startseite!");
  });

  //-----------------------------------------------------------------------------------------------------------------------------------------------

  server.on("/D0_off", []() {
    server.send(200, "text/plain", "D0 off");
    D0_off();
  });

  server.on("/D0_on", []() {
    server.send(200, "text/plain", "D0 on");
    D0_on();
  });

  server.on("/D0_setBrightness", []() {

    String message = "Number of args received:";
    for (int i = 0; i < server.args(); i++)
    {
      message += server.arg(i) + "\n";              //Get the value of the parameter
    }
    server.send(200, "text/plain", message);
    Helligkeit_Funktion(server.arg(0));
  });

  server.on("/D0_getBrightness", []() {
    server.send(200, "text/plain", String(brightness_D0));   //hier Wert 0-100
  });

  server.on("/D0_state", []() {
    if (D0_Zustand) {
      server.send(200, "text/plain", "1");
    }
    else {
      server.send(200, "text/plain", "0");
    }
  });

  server.begin();
}

void D0_off() {
  D0_Zustand = 0;

}
void D0_on() {
  D0_Zustand = 1;
}


void Helligkeit_Funktion (String Wert) {
  brightness_D0 = Wert.toInt();
  brightness_D0_map = map(brightness_D0, 0, 100, 0, 1023);

}



void D0_Funktion () {
  pinMode(d0, OUTPUT);
  brightness_D0_map_ist = map(brightness_D0_ist, 0, 1023, 0, 100);


  switch (D0_Zustand) {
    case 0:
      if (brightness_D0_ist > 0 && currentMillis - previousMillis_D0 >= interval_D0) {
        previousMillis_D0 = currentMillis;
        brightness_D0_ist = brightness_D0_ist - 1;
      }
      analogWrite(d0, brightness_D0_ist);
      brightness_LED_ist = map(brightness_D0_ist, 0, 1023, 0, 255);
      if (brightness_LED_ist_alt != brightness_LED_ist) {
        brightness_LEDR_ist = brightness_LED_ist;
        brightness_LEDG_ist = map(brightness_LED_ist, 0, 255, 0, 55);
        brightness_LEDB_ist = map(brightness_LED_ist, 0, 255, 0, 0);

        for (int zz = 0; zz <=  NUMPIXELS; zz++) {
          pixels.setPixelColor(zz, pixels.Color(brightness_LEDR_ist, brightness_LEDG_ist, brightness_LEDB_ist)); // color
        }
        pixels.show();
      }
      brightness_LED_ist_alt = brightness_LED_ist;
      break;

    case 1:
      if (brightness_D0_ist < brightness_D0_map && brightness_D0_ist <= 1023 && currentMillis - previousMillis_D0 >= interval_D0) {
        brightness_D0_ist++;
        previousMillis_D0 = currentMillis;
      }
      else if (brightness_D0_ist > brightness_D0_map && brightness_D0_ist >= 0 && currentMillis - previousMillis_D0 >= interval_D0) {
        brightness_D0_ist = brightness_D0_ist - 1;
        previousMillis_D0 = currentMillis;
      }
      analogWrite(d0, brightness_D0_ist);
      brightness_LED_ist = map(brightness_D0_ist, 0, 1023, 0, 255);
      if (brightness_LED_ist_alt != brightness_LED_ist) {
        brightness_LEDR_ist = brightness_LED_ist;
        brightness_LEDG_ist = map(brightness_LED_ist, 0, 255, 0, 55);
        brightness_LEDB_ist = map(brightness_LED_ist, 0, 255, 0, 0);

        for (int zz = 0; zz <=  NUMPIXELS; zz++) {
          pixels.setPixelColor(zz, pixels.Color(brightness_LEDR_ist, brightness_LEDG_ist, brightness_LEDB_ist)); // color
        }
        pixels.show();
      }
      brightness_LED_ist_alt = brightness_LED_ist;
      break;
    default:
      D0_Zustand = 0;
      break;
  }
}


void WiFineuverbinden() {
  if (WiFi.status() != WL_CONNECTED && currentMillis - previousMillis_WiFi >= interval_WiFi) {
    previousMillis_WiFi = currentMillis;
    WiFi.begin(ssid, password);
  }
}

void loop() {
  currentMillis = millis();
  server.handleClient();
  D0_Funktion();   //Aufruf der D0 Funktion
  WiFineuverbinden();
}
