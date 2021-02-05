#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

const char* ssid = "FRITZ!Box 7590 OD";
const char* password = "74261147202479436268";
// following for the name of: http://name_esp.local/
const char* dns_name = "esp8268";




//Pins
int d0 = 16;
int d1 = 5;
int d2 = 4;
int d3 = 0;   //(10k Pull-up)
int d4 = 2;   //(10k Pull-up) Das ist die interne Blaue LED
int d5 = 14;
int d6 = 12;
int d7 = 13;
int d8 = 15;  //(10k Pull-down leicht zu merken...)
int d9 = 3;   //RX nur bei abgeschaltetem Serial nutzbar
int d10 = 1;  //TX nur bei abgeschaltetem Serial nutzbar

int D0_Zustand = 0;
int D1_Zustand = 0;
int D2_Zustand = 0;
int D3_Zustand = 0;
int D4_Zustand = 0;
int D5_Zustand = 0;
int D6_Zustand = 0;
int D7_Zustand = 0;
int D8_Zustand = 0;
//int D9_Zustand = 0;
int D10_Zustand = 0;
int LED_Zustand = 0;

//char Wert;

int ZustandD0_temp = 0;
int ZustandD1_temp = 0;
int ZustandD2_temp = 0;
int ZustandD3_temp = 0;
int ZustandD4_temp = 0;
int ZustandD5_temp = 0;
int ZustandD6_temp = 0;
int ZustandD7_temp = 0;
int ZustandD8_temp = 0;
//int ZustandD9_temp = 0;
int ZustandD10_temp = 0;
int ZustandLED_temp = 0;


unsigned long currentMillis = 0; // nicht verändern/ nicht von Interesse


unsigned long previousMillis_WiFi = 0; //nicht verändern/ nicht von Interesse
const unsigned short interval_WiFi = 20000; //Dauer bis die WiFi erneut eingeschaltet werden darf 20 Sekunden

unsigned long previousMillis_Netzteil = 0;  //nicht verändern/ nicht von Interesse
const unsigned short interval_Netzteil = 60000; //Dauer bis das Netzteil ausgeschaltet wird 60 Sekunden

unsigned short interval_D0 = 10;
unsigned long previousMillis_D0 = 0;

unsigned short interval_LED = 10;
unsigned long previousMillis_LED = 0;


int brightness_D0 = 0;     // how bright the LED is
int brightness_D0_ist = 0;     // how bright the LED is
int brightness_D0_map = 0; // how bright the LED is in%
int brightness_D0_map_ist = 0;

int brightness_D1 = 1023;    // how bright the LED is
int brightness_D1_ist = 0;     // how bright the LED is
int brightness_D1_map = 0; // how bright the LED is in%

int brightness_D2 = 0;    // how bright the LED is
int brightness_D2_map = 0; // how bright the LED is in%

int brightness_D3 = 0;    // how bright the LED is
int brightness_D3_map = 0; // how bright the LED is in%

int brightness_D4 = 0;    // how bright the LED is
int brightness_D4_map = 0; // how bright the LED is in%

int brightness_D5 = 0;    // how bright the LED is
int brightness_D5_map = 0; // how bright the LED is in%

int brightness_D6 = 0;    // how bright the LED is
int brightness_D6_map = 0; // how bright the LED is in%

int brightness_D7 = 0;    // how bright the LED is
int brightness_D7_map = 0; // how bright the LED is in%

int brightness_D8 = 0;    // how bright the LED is
int brightness_D8_map = 0; // how bright the LED is in%

//int brightness_D9 = 0;    // how bright the LED is
//int brightness_D9_map = 0; // how bright the LED is in%

int brightness_D10 = 0;    // how bright the LED is
int brightness_D10_map = 0; // how bright the LED is in%

int brightness_LED = 0;     // how bright the LED is
int brightness_LED_ist = 0;     // how bright the LED is
int brightness_LED_map = 0; // how bright the LED is in%
int brightness_LED_map_ist = 0;



void setup()
{

  IPAddress ip(192, 168, 178, 221);
  IPAddress gateway(192, 168, 178, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(192, 168, 178, 1);
  WiFi.config(ip, dns, gateway, subnet);
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);

  /////////////////change pin to gpio////////
  //GPIO 1 (TX) swap the pin to a GPIO.
  pinMode(1, FUNCTION_3);
  //GPIO 3 (RX) swap the pin to a GPIO.
  pinMode(3, FUNCTION_3);
  ///////////////////////

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


  server.on("/D0_wechsle", [] () {
    server.send(200, "text/plain", "D0 wechsle!");
    D0_wechsle();//Aufruf der Funktion
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
  //-----------------------------------------------------------------------------------------------------------------------------------------------


  server.on("/D1_off", []() {
    server.send(200, "text/plain", "D1 off");
    D1_off();
  });

  server.on("/D1_on", []() {
    server.send(200, "text/plain", "D1 on");
    D1_on();
  });


  server.on("/D1_wechsle", [] () {
    server.send(200, "text/plain", "D1 wechsle!");
    D1_wechsle();//Aufruf der Funktion
  });

  server.on("/D1_state", []() {
    if (D1_Zustand) {
      server.send(200, "text/plain", "ON");
    }
    else {
      server.send(200, "text/plain", "OFF");
    }
  });




  //-----------------------------------------------------------------------------------------------------------------------------------------------

  server.on("/D2_off", []() {
    server.send(200, "text/plain", "D2 off");
    D2_off();
  });

  server.on("/D2_on", []() {
    server.send(200, "text/plain", "D2 on");
    D2_on();
  });


  server.on("/D2_wechsle", [] () {
    server.send(200, "text/plain", "D2 wechsle!");
    D2_wechsle();//Aufruf der Funktion
  });

  server.on("/D2_state", []() {
    if (D2_Zustand) {
      server.send(200, "text/plain", "ON");
    }
    else {
      server.send(200, "text/plain", "OFF");
    }
  });


  //-----------------------------------------------------------------------------------------------------------------------------------------------

  server.on("/D3_off", []() {
    server.send(200, "text/plain", "D3 off");
    D3_off();
  });

  server.on("/D3_on", []() {
    server.send(200, "text/plain", "D3 on");
    D3_on();
  });


  server.on("/D3_wechsle", [] () {
    server.send(200, "text/plain", "D3 wechsle!");
    D3_wechsle();//Aufruf der Funktion
  });

  server.on("/D3_state", []() {
    if (D3_Zustand) {
      server.send(200, "text/plain", "ON");
    }
    else {
      server.send(200, "text/plain", "OFF");
    }
  });


  //-----------------------------------------------------------------------------------------------------------------------------------------------


  server.on("/D4_off", []() {
    server.send(200, "text/plain", "D4 off");
    D4_off();
  });

  server.on("/D4_on", []() {
    server.send(200, "text/plain", "D4 on");
    D4_on();
  });


  server.on("/D4_wechsle", [] () {
    server.send(200, "text/plain", "D4 wechsle!");
    D4_wechsle();//Aufruf der Funktion
  });

  server.on("/D4_state", []() {
    if (D4_Zustand) {
      server.send(200, "text/plain", "ON");
    }
    else {
      server.send(200, "text/plain", "OFF");
    }
  });

  //-----------------------------------------------------------------------------------------------------------------------------------------------

  server.on("/D5_off", []() {
    server.send(200, "text/plain", "D5 off");
    D5_off();
  });

  server.on("/D5_on", []() {
    server.send(200, "text/plain", "D5 on");
    D5_on();
  });


  server.on("/D5_wechsle", [] () {
    server.send(200, "text/plain", "D5 wechsle!");
    D5_wechsle();//Aufruf der Funktion
  });

  server.on("/D5_state", []() {
    if (D5_Zustand) {
      server.send(200, "text/plain", "ON");
    }
    else {
      server.send(200, "text/plain", "OFF");
    }
  });


  //-----------------------------------------------------------------------------------------------------------------------------------------------

  server.on("/D6_off", []() {
    server.send(200, "text/plain", "D6 off");
    D6_off();
  });

  server.on("/D6_on", []() {
    server.send(200, "text/plain", "D6 on");
    D6_on();
  });

  server.on("/D6_wechsle", [] () {
    server.send(200, "text/plain", "D6 wechsle!");
    D6_wechsle();//Aufruf der Funktion
  });

  server.on("/D6_state", []() {
    if (D6_Zustand) {
      server.send(200, "text/plain", "ON");
    }
    else {
      server.send(200, "text/plain", "OFF");
    }
  });


  //-----------------------------------------------------------------------------------------------------------------------------------------------

  server.on("/D7_off", []() {
    server.send(200, "text/plain", "D7 off");
    D7_off();
  });

  server.on("/D7_on", []() {
    server.send(200, "text/plain", "D7 on");
    D7_on();
  });

  server.on("/D7_wechsle", [] () {
    server.send(200, "text/plain", "D7 wechsle!");
    D7_wechsle();//Aufruf der Funktion
  });

  server.on("/D7_state", []() {
    if (D7_Zustand) {
      server.send(200, "text/plain", "ON");
    }
    else {
      server.send(200, "text/plain", "OFF");
    }
  });


  //-----------------------------------------------------------------------------------------------------------------------------------------------

  server.on("/D8_off", []() {
    server.send(200, "text/plain", "D8 off");
    D8_off();
  });

  server.on("/D8_on", []() {
    server.send(200, "text/plain", "D8 on");
    D8_on();
  });

  server.on("/D8_wechsle", [] () {
    server.send(200, "text/plain", "D8 wechsle!");
    D8_wechsle();//Aufruf der Funktion
  });

  server.on("/D8_state", []() {
    if (D8_Zustand) {
      server.send(200, "text/plain", "ON");
    }
    else {
      server.send(200, "text/plain", "OFF");
    }
  });


  //-----------------------------------------------------------------------------------------------------------------------------------------------

  /*
    server.on("/D9_off", []() {
      server.send(200, "text/plain", "D9 off");
      D9_off();
    });

    server.on("/D9_on", []() {
      server.send(200, "text/plain", "D9 on");
      D9_on();
    });

    server.on("/D9_wechsle", [] () {
      server.send(200, "text/plain", "D9 wechsle!");
      D9_wechsle();//Aufruf der Funktion
    });

    server.on("/D9_state", []() {
      if (D9_Zustand) {
        server.send(200, "text/plain", "ON");
      }
      else {
        server.send(200, "text/plain", "OFF");
      }
    });

  */
  //-----------------------------------------------------------------------------------------------------------------------------------------------

  server.on("/D10_off", []() {
    server.send(200, "text/plain", "D10 off");
    D10_off();
  });

  server.on("/D10_on", []() {
    server.send(200, "text/plain", "D10 on");
    D10_on();
  });

  server.on("/D10_wechsle", [] () {
    server.send(200, "text/plain", "D10 wechsle!");
    D10_wechsle();//Aufruf der Funktion
  });

  server.on("/D10_state", []() {
    if (D10_Zustand) {
      server.send(200, "text/plain", "ON");
    }
    else {
      server.send(200, "text/plain", "OFF");
    }
  });

  //---------------------------------------------------------------------------------------------------------------------------------------------

  server.on("/LED_off", []() {
    server.send(200, "text/plain", "LED off");
    LED_off();
  });

  server.on("/LED_on", []() {
    server.send(200, "text/plain", "LED on");
    LED_on();
  });


  server.on("/LED_setBrightness", []() {

    String message = "Number of args received:";
    for (int i = 0; i < server.args(); i++)
    {
      message += server.arg(i) + "\n";              //Get the value of the parameter
    }
    server.send(200, "text/plain", message);
    Helligkeit_Funktion_2(server.arg(0));
  });

  server.on("/LED_getBrightness", []() {
    server.send(200, "text/plain", String(brightness_LED));   //hier Wert 0-100
  });



  server.on("/LED_state", []() {
    if (LED_Zustand) {
      server.send(200, "text/plain", "1");
    }
    else {
      server.send(200, "text/plain", "0");
    }
  });
  //--------------------------------------------------------------------------------------------------------


  server.begin();
}


void D0_off() {
  D0_Zustand = 0;

}
void D0_on() {
  D0_Zustand = 1;
  D8_Zustand = 1;
  D8_Funktion();
  delay(500);
}

void D0_wechsle () {
  if (digitalRead(d0) || D0_Zustand == 2 || D0_Zustand == 3) {
    D0_Zustand = 0;
  }
  else {
    D0_Zustand = 1;
  }
}

void Helligkeit_Funktion (String Wert) {
  brightness_D0 = Wert.toInt();
  brightness_D0_map = map(brightness_D0, 0, 100, 0, 1023);
}


void D1_off() {
  D1_Zustand = 0;
}
void D1_on() {
  D1_Zustand = 1;

}

void D1_wechsle () {
  if (digitalRead(d1) || D1_Zustand == 2 || D1_Zustand == 3) {
    D1_Zustand = 0;
  }
  else {
    D1_Zustand = 1;
  }
}

void D2_off() {
  D2_Zustand = 0;
}
void D2_on() {
  D2_Zustand = 1;
}

void D2_wechsle () {
  if (digitalRead(d2) || D2_Zustand == 2 || D2_Zustand == 3) {
    D2_Zustand = 0;
  }
  else {
    D2_Zustand = 1;
  }
}

void D3_off() {
  D3_Zustand = 0;
}
void D3_on() {
  D3_Zustand = 1;
}

void D3_wechsle () {
  if (digitalRead(d3) || D3_Zustand == 2 || D3_Zustand == 3) {
    D3_Zustand = 0;
  }
  else {
    D3_Zustand = 1;
  }
}

void D4_off() {
  D4_Zustand = 0;
  D0_Zustand = 0;
  D1_Zustand = 0;
  D2_Zustand = 0;
  D3_Zustand = 0;
  D5_Zustand = 0;
  D6_Zustand = 0;
  D7_Zustand = 0;
  D8_Zustand = 0;
  //D9_Zustand = 0;
  D10_Zustand = 0;
}
void D4_on() {
  D4_Zustand = 1;
}
void D4_wechsle () {
  if (digitalRead(d4) || D4_Zustand == 2 || D4_Zustand == 3) {
    D4_Zustand = 0;
  }
  else {
    D4_Zustand = 1;
  }
}

void D5_off() {
  D5_Zustand = 0;
}
void D5_on() {
  D5_Zustand = 1;
}

void D5_wechsle () {
  if (digitalRead(d5) || D5_Zustand == 2 || D5_Zustand == 3) {
    D5_Zustand = 0;
  }
  else {
    D5_Zustand = 1;
  }
}

void D6_off() {
  D6_Zustand = 0;
}
void D6_on() {
  D6_Zustand = 1;
}
void D6_wechsle () {
  if (digitalRead(d6) || D6_Zustand == 2 || D6_Zustand == 3) {
    D6_Zustand = 0;
  }
  else {
    D6_Zustand = 1;
  }
}

void D7_off() {
  D7_Zustand = 0;
  D5_Zustand = 0;
}
void D7_on() {
  D7_Zustand = 1;
  D5_Zustand = 1;
}

void D7_wechsle () {
  if (digitalRead(d7) || D7_Zustand == 2 || D7_Zustand == 3) {
    D7_Zustand = 0;
  }
  else {
    D7_Zustand = 1;
  }
}

void D8_off() {
  D8_Zustand = 0;
}
void D8_on() {
  D8_Zustand = 1;
}

void D8_wechsle () {
  if (digitalRead(d8) || D8_Zustand == 2 || D8_Zustand == 3) {
    D8_Zustand = 0;
  }
  else {
    D8_Zustand = 1;
  }
}
/*
  void D9_off() {
  D9_Zustand = 0;
  }
  void D9_on() {
  D9_Zustand = 1;
  }

  void D9_wechsle () {
  if (digitalRead(d9) || D9_Zustand == 2 || D9_Zustand == 3) {
    D9_Zustand = 0;
  }
  else {
    D9_Zustand = 1;
  }
  }
*/

void D10_off() {
  D10_Zustand = 0;
}
void D10_on() {
  D10_Zustand = 1;
}
void D10_wechsle () {
  if (digitalRead(d10) || D10_Zustand == 2 || D10_Zustand == 3) {
    D10_Zustand = 0;
  }
  else {
    D10_Zustand = 1;
  }
}


void LED_off() {
  LED_Zustand = 0;

}
void LED_on() {
  LED_Zustand = 1;
}


void Helligkeit_Funktion_2 (String Wert_LED) {
  brightness_LED = Wert_LED.toInt();
  brightness_LED_map = map(brightness_LED, 0, 100, 0, 255);
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
      else if (brightness_D0_ist == 0) {
        D1_Zustand = 0;                //Lüfter
        D8_Zustand = 0;                //Netzteil
      }
      analogWrite(d0, brightness_D0_ist);
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
      D1_Zustand = 1;                 //Lüfter
      D8_Zustand = 1;                 //Netzteil
      break;
    default:
      D0_Zustand = 0;
      break;
  }
}


void D1_Funktion () {
  pinMode(d1, OUTPUT);
  switch (D1_Zustand) {
    case 0: analogWrite(d1, 0);
      break;
    case 1: analogWrite(d1, brightness_D1);
      break;
    default:
      D1_Zustand = D0_Zustand;
      break;

  }
}

void D2_Funktion () {
  switch (D2_Zustand) {
    case 0: pinMode(d2, INPUT);

      break;
    case 1: pinMode(d2, OUTPUT);
      digitalWrite(d2, HIGH);
      break;
    default:
      D2_Zustand = 0;
      break;

  }
}

void D3_Funktion () {
  switch (D3_Zustand) {
    case 0: digitalWrite(d3, LOW);

      break;
    case 1: pinMode(d3, OUTPUT);
      digitalWrite(d3, HIGH);
      break;
    default:
      D3_Zustand = 0;
      break;

  }
}

void D4_Funktion () {
  switch (D4_Zustand) {
    case 0:
      pinMode(d4, INPUT);
      break;
    case 1: pinMode(d4, OUTPUT);
      digitalWrite(d4, LOW);
      break;
    default:
      D4_Zustand = 0;
      break;

  }
}

void D5_Funktion () {
  switch (D5_Zustand) {
    case 0: pinMode(d5, INPUT);
      break;
    case 1: pinMode(d5, OUTPUT);
      digitalWrite(d5, HIGH);
      break;
    default:
      D5_Zustand = 0;
      break;

  }
}

void D6_Funktion () {
  switch (D6_Zustand) {
    case 0: pinMode(d6, INPUT);

      break;
    case 1: pinMode(d6, OUTPUT);
      digitalWrite(d6, HIGH);
      break;
    default:
      D6_Zustand = 0;
      break;
  }
}


void D7_Funktion () {
  switch (D7_Zustand) {
    case 0: pinMode(d7, INPUT);

      break;
    case 1: pinMode(d7, OUTPUT);
      digitalWrite(d7, HIGH);
      break;
    default:
      D7_Zustand = 0;
      break;

  }
}


void D8_Funktion () {
  switch (D8_Zustand) {
    case 0: pinMode(d8, INPUT);

      break;
    case 1: pinMode(d8, OUTPUT);
      digitalWrite(d8, HIGH);
      break;
    default:
      D8_Zustand = 0;
      break;

  }
}
/*
  void D9_Funktion () {
  switch (D9_Zustand) {
    case 0: pinMode(d9, INPUT);

      break;
    case 1: pinMode(d9, OUTPUT);
      digitalWrite(d9, HIGH);
      break;
    default:
      D9_Zustand = 0;
      break;

  }
  }
*/
void D10_Funktion () {
  D10_Zustand = D0_Zustand;
  switch (D10_Zustand) {
    case 0: pinMode(d10, INPUT);

      break;
    case 1: pinMode(d10, OUTPUT);
      digitalWrite(d10, HIGH);
      break;
    default:
      D10_Zustand = 0;
      break;

  }
}

void D9_Funktion() {

  brightness_LED_map_ist = map(brightness_LED_ist, 0, 255, 0, 100);

  switch (LED_Zustand) {
    case 0:
      if (brightness_LED_ist > 0 && currentMillis - previousMillis_LED >= interval_LED) {
        previousMillis_LED = currentMillis;
        brightness_LED_ist = brightness_LED_ist - 1;
      }
      analogWrite(d9, brightness_LED_ist);
      break;

    case 1:
      if (brightness_LED_ist < brightness_LED_map && brightness_LED_ist <= 255 && currentMillis - previousMillis_LED >= interval_LED) {
        brightness_LED_ist++;
        previousMillis_LED = currentMillis;
      }
      else if (brightness_LED_ist > brightness_LED_map && brightness_LED_ist >= 0 && currentMillis - previousMillis_LED >= interval_LED) {
        brightness_LED_ist = brightness_LED_ist - 1;
        previousMillis_LED = currentMillis;
      }
      analogWrite(d9, brightness_LED_ist);
      break;
    default:
      LED_Zustand = 0;
      break;
  }
}



void WiFineuverbinden() {
  if (WiFi.status() != WL_CONNECTED && currentMillis - previousMillis_WiFi >= interval_WiFi) {
    previousMillis_WiFi = currentMillis;
    WiFi.begin(ssid, password);
  }
}
void Netzteil_ausschalten () {
  if (D0_Zustand == 0 && D1_Zustand == 0 && D2_Zustand == 0 && D3_Zustand == 0 && D5_Zustand == 0 && D6_Zustand == 0 && D7_Zustand == 0 && D8_Zustand == 0 &&  D10_Zustand == 0 && LED_Zustand == 0) {
    //if (currentMillis - previousMillis_Netzteil >= interval_Netzteil) {
    D4_off(); //Netzteil_ausschalten
    //}
  }
}


void Netzteil_einschalten () {
  if (D0_Zustand == 1 || D1_Zustand == 1 || D2_Zustand == 1 || D3_Zustand == 1 || D5_Zustand == 1 || D6_Zustand == 1 || D7_Zustand == 1 || D8_Zustand == 1 || D10_Zustand == 1 || LED_Zustand == 1) {
    //previousMillis_Netzteil = currentMillis;
    D4_Zustand = 1; //Netzteil_einschalten
  }
}


void loop() {
  currentMillis = millis();
  server.handleClient();
  D0_Funktion();   //Aufruf der D0 Funktion
  D1_Funktion();   //Aufruf der D1 Funktion
  D2_Funktion();   //Aufruf der D2 Funktion
  D3_Funktion();   //Aufruf der D3 Funktion
  D5_Funktion();   //Aufruf der D5 Funktion
  D6_Funktion();   //Aufruf der D6 Funktion
  D7_Funktion();   //Aufruf der D7 Funktion
  D8_Funktion();   //Aufruf der D8 Funktion
  D9_Funktion();   //Aufruf der D9 Funktion
  D10_Funktion();   //Aufruf der D10 Funktion
  Netzteil_einschalten();   //Aufruf der Funktion Netzteil_einschalten
  D4_Funktion();   //Aufruf der D4 Funktion
  WiFineuverbinden();
  Netzteil_ausschalten(); //Aufruf der Funktion Netzteil_ausschalten

}
