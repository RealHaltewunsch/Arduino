#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7
#define LED8 8
#define LED9 9
#define LED10 10

int Torstand = 0;
int neu;
int alt = LOW;
int zustand;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  // put your setup code here, to run once:
  /*
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);

    delay(2000);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  */

  /*Startschleife*/


  for (int i = 0; i <= 1; i++) { //2 mal blinkend durchlaufen


    for (int i = 0; i <= 10; i++) {
      pinMode (i, OUTPUT);
      digitalWrite(i, HIGH);
      delay(50);
      digitalWrite(i, LOW);
    }

    for (int i = 10; i >= 1; i--) {
      pinMode (i, OUTPUT);
      digitalWrite(i, HIGH);
      delay(50);
      digitalWrite(i, LOW);
    }
  }
  for (int i = 0; i <= 10; i++) { //Leuchtend durchlaufen und wieder erlischen
    pinMode (i, OUTPUT);
    digitalWrite(i, HIGH);
    delay(150);
  }
  for (int i = 10; i >= 0; i--) {
    pinMode (i, OUTPUT);
    delay(150);
    digitalWrite(i, LOW);
  }

  pinMode(11, INPUT_PULLUP); //stabieleres Input

}

void loop() {
  // put your main code here, to run repeatedly:
  neu = digitalRead(11);

  if (neu != alt) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }


  if ((millis() - lastDebounceTime) > debounceDelay) { //Input Pullup ungedrückt eine 1, normales input gibt ungedrückt eine 0, entweder ==0 oder invertieren mit ! vor digitalRead
    if (neu != zustand) {
      zustand = neu;
      // reset the debouncing timer
      if (zustand == 0) {
        Torstand ++;
        Torzahl(Torstand);
      }
    }
  }

  alt = neu;
}

void Torzahl(int a) {
  switch (a) {
    case 0:  for (int i = 10; i >= 0; i--) {
        digitalWrite(i, LOW);
      }
      break;
    case 1: digitalWrite(LED1, HIGH);
      break;
    case 2: digitalWrite(LED2, HIGH);
      break;
    case 3: digitalWrite(LED3, HIGH);
      break;
    case 4: digitalWrite(LED4, HIGH);
      break;
    case 5: digitalWrite(LED5, HIGH);
      break;
    case 6: digitalWrite(LED6, HIGH);
      break;
    case 7: digitalWrite(LED7, HIGH);
      break;
    case 8: digitalWrite(LED8, HIGH);
      break;
    case 9: digitalWrite(LED9, HIGH);
      break;
    case 10: digitalWrite(LED10, HIGH);
      break;
    default:
      break;
  }

}
