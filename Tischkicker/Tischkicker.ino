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

int led9state = LOW;             // ledState used to set the LED

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 500;           // interval at which to blink (milliseconds)
unsigned long currentMillis = millis();


void setup() {
  // put your setup code here, to run once:
  /*Startschleife*/
  for (int i = 0; i <= 1; i++) { //2 mal blinkend durchlaufen

    for (int i = 0; i <= 10; i++) {
      pinMode (i, OUTPUT);
      digitalWrite(i, HIGH);
      delay(50);
      if (i == 10) {
        pinMode(i, INPUT);
      }
      else {
        digitalWrite(i, LOW);
      }
    }

    for (int i = 10; i >= 1; i--) {
      pinMode (i, OUTPUT);
      digitalWrite(i, HIGH);
      delay(50);
      if (i == 10) {
        pinMode(i, INPUT);
      }
      else {
        digitalWrite(i, LOW);
      }
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
    if (i == 10) {
      pinMode(i, INPUT);
    }
    else {
      digitalWrite(i, LOW);
    }
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

      }
    }
  }
  alt = neu;
  Torzahl(Torstand);
}

void Torzahl(int a) {
  switch (a) {
    case 0:  for (int i = 10; i >= 0; i--) {
        if (i == 10) {
          pinMode(i, INPUT);
        }
        else {
          digitalWrite(i, LOW);
        }
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
    case 9: currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (led9state == LOW) {
          led9state = HIGH;
        } else {
          led9state = LOW;
        }
      }
      digitalWrite(LED9, led9state);
      break;
    case 10:



      for (int f = 0; f <= 10; f++) { //Leuchtend durchlaufen und wieder erlischen
        if (f == 10) {
          pinMode (LED10, OUTPUT);
        }
        digitalWrite(f, HIGH);
      }




      delay(interval / 2); //Intervallzeit sieg

      for (int r = 0; r <= 10; r++) { //Leuchtend durchlaufen und wieder erlischen
        if (r == 10) {
          pinMode (LED10, INPUT);
        }
        else {
          digitalWrite(r, LOW);
        }
      }
      delay(interval / 3); //Intervallzeit sieg
      break;
    default:
      break;
  }
}
