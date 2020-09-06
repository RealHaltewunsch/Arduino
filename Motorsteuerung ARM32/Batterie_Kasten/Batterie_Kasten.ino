#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2      // Data wire is plugged into pin 2 on the Arduino
#define Master_In 3         //Wenn der PIN LOW ist, ist ein anderer Master anwesend
#define Lüfter_PWM 9        //Über diesen PIN wird die Drehzahl vorgegeben
#define MOSFET 4            //Wenn Kühlung benötigt wird, so wird dieser PIN HIGH geschaltet, so werden die Lüfter eingeschaltet

#define MAX_AKKU 60
#define MIN_AKKU 40

uint8_t Temperatursensor_Akku_1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_2[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_3[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_4[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_5[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t Temperatursensor_Akku_6[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

bool Master = false;  //wenn Master true, dann ist dieser Arduino der Master des ONE-Wire Bus

void setup() {
  // put your setup code here, to run once:
  pinMode(INPUT_PULLUP, Master_In);
  pinMode(OUTPUT, Lüfter_PWM);
  pinMode(OUTPUT, MOSFET);
  attachInterrupt(digitalPinToInterrupt(Master_In), ISR, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void Temperaturen () {  //bei jedem Durchlauf wird nur ein anderer Temperatursensor angesprochen, das verringert die Durchlaufzeit.
  switch (Temperaturzaehler) {
    case 0:
      Temperatur_Akku_1 = sensors.getTempC(Temperatursensor_Akku_1);
      Temperaturzaehler++;
      break;
    case 1:
      Temperatur_Akku_2 = sensors.getTempC(Temperatursensor_Akku_2);
      Temperatur_Akku_Min = min (Temperatur_Akku_1, Temperatur_Akku_2);  //hier wird Akku_Min zurückgesetzt
      Temperatur_Akku_Max = max (Temperatur_Akku_1, Temperatur_Akku_2);  //hier wird Akku_Max zurückgesetzt
      Temperaturzaehler++;
      break;
    case 2:
      Temperatur_Akku_3 = sensors.getTempC(Temperatursensor_Akku_3);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_3);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_3);
      Temperaturzaehler++;
      break;
    case 3:
      Temperatur_Akku_4 = sensors.getTempC(Temperatursensor_Akku_4);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_4);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_4);
      Temperaturzaehler++;
      break;
    case 4:
      Temperatur_Akku_5 = sensors.getTempC(Temperatursensor_Akku_5);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_5);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_5);
      Temperaturzaehler++;
      break;
    case 5:
      Temperatur_Akku_6 = sensors.getTempC(Temperatursensor_Akku_6);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_6);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_6);
      Temperaturzaehler = 0;
      break;
    default:
      Temperaturzaehler = 0;
      break;
  }
}

void ISR () {
Master = digitalRead(Master_In);
}
