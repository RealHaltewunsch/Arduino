#include <TMCStepper.h>

#define EN_PIN            D1 // Enable
#define DIR_PIN           D2 // Direction
#define STEP_PIN          D3 // Step
#define STALLGUARD_PIN    D4 // Stallguard
#define TASTER_PIN        D5 // Taste für manuellen Request 
#define LAMPE_PIN         D6 // Lampe des Tasters
#define SSR_PIN           D7 // SSR für Netzteil
#define SERIAL_PORT Serial   // TMC2208/TMC2224 HardwareSerial port
#define DRIVER_ADDRESS 0b00  // TMC2209 Driver address according to MS1 and MS2

#define R_SENSE 0.11f

TMC2209Stepper driver(&SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);

void setup() {
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STALLGUARD_PIN, INPUT_PULLUP);
  pinMode(TASTER_PIN, INPUT_PULLUP);
  pinMode(LAMPE_PIN, OUTPUT);
  pinMode(SSR_PIN, OUTPUT);

  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware

  attachInterrupt(digitalPinToInterrupt(STALLGUARD_PIN), ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(TASTER_PIN), Taster, CHANGE);

  SERIAL_PORT.begin(115200);      // HW UART drivers
  driver.begin();                 //  SPI: Init CS pins and possible SW SPI pins
  driver.toff(5);                 // Enables driver in software
  driver.rms_current(600);        // Set motor RMS current
  driver.microsteps(16);          // Set microsteps to 1/16th
  driver.en_spreadCycle(true);   // Toggle spreadCycle on TMC2208/2209/2224
  driver.pwm_autoscale(true);     // Needed for stealthChop
}

bool shaft = false;

void loop() {
  // Run 5000 steps and switch direction in software
  for (uint16_t i = 5000; i > 0; i--) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(160);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(160);
  }
  shaft = !shaft;
  driver.shaft(shaft);
}

void ISR () {

}

void Taster () {

}
