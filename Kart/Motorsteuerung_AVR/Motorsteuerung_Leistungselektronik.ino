void Leistungselektronik_auslesen () {  //diese Funktion dient dazu, zu erkennen, dass die Leistungselektronik eingeschaltet wird. Wenn der PIN HIGH wird, wird 3s gewartet, und dann werden die Einstellungen zur Leistungselektronik gesendet.

  Leistungselektronik = !digitalRead(Leistungselektronik_PIN);

  if (!Leistungselektronik_check && Leistungselektronik) {
    previousMillis_Leistungselektronik = currentMillis;
    Leistungselektronik_check = true;
  }

  if (Leistungselektronik_check && currentMillis - previousMillis_Leistungselektronik >= interval_Leistungselektronik) {
    Leistungselektronik_start = true;
    Leistungselektronik_check = false;
  }
}
