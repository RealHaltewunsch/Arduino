#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2      // Data wire is plugged into pin 2 on the Arduino
#define Master_In 3         //Wenn der PIN LOW ist, ist ein anderer Master anwesend
#define Lüfter_PWM 9        //Über diesen PIN wird die Drehzahl vorgegeben
#define MOSFET 4            //Wenn Kühlung benötigt wird, so wird dieser PIN HIGh geschaltet, so werden die Lüfter eingeschaltet


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

void ISR () {

}
