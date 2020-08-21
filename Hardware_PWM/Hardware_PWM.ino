#include <TimerOne.h>
long int Faktor = 1000000;
long int Frequenz = 1000; //Frequenz in Hertz
int Periode = 0; //Periodendauer in uS
int sensorPin = A0; 
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
Periode = Faktor / Frequenz;
pinMode(10,OUTPUT);
Timer1.initialize(Periode);  //
Timer1.start();
}

void loop() {
  // put your main code here, to run repeatedly:
Timer1.pwm(10,512);
}
