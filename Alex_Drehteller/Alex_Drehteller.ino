#include "BasicStepperDriver.h"
#include "A4988.h"
#define MOTOR_STEPS 200
#define MICROSTEPS 1

// Acceleration and deceleration values are always in FULL steps / s^2
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000

#define EN_PIN        4 // Enable
#define DIR_PIN       11 // Direction
#define STEP_PIN      10 // Step
#define MS1           7
#define MS2           8
#define MS3           9
#define Gruen         3
#define Gelb          5
#define Rot           6
#define Schalter       2
#define Batterie      A0
#define Poti          A1
#define Power_Poti    A2

//BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN, EN_PIN);

A4988 stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN, MS1 , MS2 , MS3);

bool dir = false;
bool schalter_state = false;

int motorspeed = 1;    // how fast
//int distance = 360;

int SOC = 0;

void setup() {
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(Gruen, OUTPUT);
  pinMode(Gelb, OUTPUT);
  pinMode(Rot, OUTPUT);
  pinMode(Power_Poti, OUTPUT);
  pinMode(Poti, INPUT);
  pinMode(Batterie, INPUT);
  pinMode(Schalter, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Schalter), Schalter_auslesen, CHANGE); //Interrupt an den BREMSE_PIN
  Schalter_auslesen ();


  digitalWrite(Power_Poti, HIGH);
  Read_Speed ();
  read_SOC ();
  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  //stepper.rotate(360);
  Read_Speed ();
  read_SOC ();
  stepper.begin(motorspeed, MICROSTEPS);
  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  stepper.startRotate(motorspeed);
}



void loop() {
  Read_Speed ();
  read_SOC ();
  //stepper.rotate(distance);
  //stepper.move(motorspeed);
  one_Step(motorspeed);
}

void Schalter_auslesen () {
  schalter_state = !digitalRead(Schalter);
}

void one_Step(unsigned short int delayinmicro) {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(delayinmicro);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(delayinmicro);
}

void Read_Speed () {
  int analogValue = analogRead(Poti);

  if (analogValue >= 511 ) {
    dir = true;
  }
  else {
    dir = false;
  }
  digitalWrite(DIR_PIN, dir);

  if (analogValue >= 470 && analogValue <= 552 || schalter_state || SOC <= 10) {   //stehen bleiben
    digitalWrite(EN_PIN, HIGH);      // Disable driver in hardware
    //stepper.disable();
  }
  else {
    //stepper.enable();
    digitalWrite(EN_PIN, LOW);      // Enable driver in hardware
  }
  if (analogValue <= 470) {
    motorspeed = map(analogValue, 0, 470, 2000, 10000);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, LOW);
    digitalWrite(MS3, LOW);
  }
  if (analogValue >= 552) {
    motorspeed = map(analogValue, 552, 1023, 10000, 2000);
    digitalWrite(MS1, HIGH);
    digitalWrite(MS2, LOW);
    digitalWrite(MS3, LOW);
  }
  //stepper.setRPM(motorspeed);
}


void read_SOC () {
  int analogValue = analogRead(Batterie);
  analogValue = constrain(analogValue, 634, 838);  //3,1 bis 4,1V
  SOC = map(analogValue, 634, 838, 0, 100);

  if (SOC >= 65) {
    int PWM = map(SOC, 65, 100, 0, 255);
    analogWrite(Gruen, PWM);
  }
  else {
    analogWrite(Gruen, 0);
  }
  if (SOC >= 33) {
    int PWM = map(SOC, 33, 100, 0, 255);
    analogWrite(Gelb, PWM);
  }
  else {
    analogWrite(Gelb, 0);
  }
  if (SOC >= 10) {
    int PWM = map(SOC, 10, 100, 15, 255);
    analogWrite(Rot, PWM);
  }
  else {
    analogWrite(Rot, 15);
  }
}
