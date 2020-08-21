void Uebertemperatur_auslesen() {
  if (MAX_TEMP_AKKU_RUN <= Max_Akku_Temperatur_erfragen() || MAX_TEMP_MOTOR <= Motor_Temperatur_erfragen() || MAX_TEMP_LEISTUNGSELEKTRONIK <= Max_Leistungselektronik_Temperatur_erfragen()) { //wenn True dann Überhitzt, erweitern um die anderen Sensoren
    Timer1.disablePwm(MOSFET_PIN);
    Uebertemperatur = true;
  }
  else if (MAX_TEMP_AKKU_STARTUP - 5 > Max_Akku_Temperatur_erfragen() && MAX_TEMP_MOTOR - 20 > Motor_Temperatur_erfragen () && MAX_TEMP_LEISTUNGSELEKTRONIK - 20 > Max_Leistungselektronik_Temperatur_erfragen()) { //wenn True dann um 10 bzw. 20 Grad runter gekühlt
    Uebertemperatur = false;
  }
}

void Uebertemperatur_Startup_auslesen() {
  if (MAX_TEMP_AKKU_STARTUP <= Max_Akku_Temperatur_erfragen() || MAX_TEMP_MOTOR <= Motor_Temperatur_erfragen () || MAX_TEMP_LEISTUNGSELEKTRONIK <= Max_Leistungselektronik_Temperatur_erfragen()) { //wenn True dann Überhitzt, erweitern um die anderen Sensoren
    Timer1.disablePwm(MOSFET_PIN);
    Uebertemperatur = true;
  }
  else if (MAX_TEMP_AKKU_STARTUP - 5 > Max_Akku_Temperatur_erfragen() && MAX_TEMP_MOTOR - 20 > Motor_Temperatur_erfragen ()&& MAX_TEMP_LEISTUNGSELEKTRONIK - 20 > Max_Leistungselektronik_Temperatur_erfragen()) { //wenn True dann um 10 bzw. 20 Grad runter gekühlt
    Uebertemperatur = false;
  }
}
