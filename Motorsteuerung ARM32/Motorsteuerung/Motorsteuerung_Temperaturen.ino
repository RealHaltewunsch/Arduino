void Temperaturen () {  //bei jedem Durchlauf wird nur ein anderer Temperatursensor angesprochen, das verringert die Durchlaufzeit.
  switch (Temperaturzaehler) {
    case 0:
      Temperatur_Motor = sensors.getTempC(Temperatursensor_Motor);
      Temperaturzaehler++;
      break;
    case 1:
      Temperatur_Leistungselektronik_1 = sensors.getTempC(Temperatursensor_Leistungselektronik_1);
      Temperaturzaehler++;
      break;
    case 2:
      Temperatur_Leistungselektronik_2 = sensors.getTempC(Temperatursensor_Leistungselektronik_2);
      Temperatur_Leistungselektronik_Min = min (Temperatur_Leistungselektronik_1, Temperatur_Leistungselektronik_2);  //hier wird Leistungselektronik_Min zurückgesetzt
      Temperatur_Leistungselektronik_Max = max (Temperatur_Leistungselektronik_1, Temperatur_Leistungselektronik_2);  //hier wird Leistungselektronik_Max zurückgesetzt
      Temperaturzaehler++;
      break;
    case 3:
      /*Temperatur_Leistungselektronik_3 = sensors.getTempC(Temperatursensor_Leistungselektronik_3);
      Temperatur_Leistungselektronik_Min = min (Temperatur_Leistungselektronik_Min, Temperatur_Leistungselektronik_3);  //hier wird Leistungselektronik_Min zurückgesetzt
      Temperatur_Leistungselektronik_Max = max (Temperatur_Leistungselektronik_Max, Temperatur_Leistungselektronik_3);  //hier wird Leistungselektronik_Max zurückgesetzt
      */
      Temperaturzaehler++;
      break;
    case 4:
      Temperatur_Akku_1 = sensors.getTempC(Temperatursensor_Akku_1);
      Temperaturzaehler++;
      break;
    case 5:
      Temperatur_Akku_2 = sensors.getTempC(Temperatursensor_Akku_2);
      Temperatur_Akku_Min = min (Temperatur_Akku_1, Temperatur_Akku_2);  //hier wird Akku_Min zurückgesetzt
      Temperatur_Akku_Max = max (Temperatur_Akku_1, Temperatur_Akku_2);  //hier wird Akku_Max zurückgesetzt
      Temperaturzaehler++;
      break;
    case 6:
      Temperatur_Akku_3 = sensors.getTempC(Temperatursensor_Akku_3);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_3);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_3);
      Temperaturzaehler++;
      break;
    case 7:
      Temperatur_Akku_4 = sensors.getTempC(Temperatursensor_Akku_4);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_4);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_4);
      Temperaturzaehler++;
      break;
    case 8:
      Temperatur_Akku_5 = sensors.getTempC(Temperatursensor_Akku_5);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_5);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_5);
      Temperaturzaehler++;
      break;
    case 9:
      Temperatur_Akku_6 = sensors.getTempC(Temperatursensor_Akku_6);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_6);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_6);
      Temperaturzaehler = 0;
      break;
    default:
      Temperaturzaehler = 0;
      break;
  }
  if (Temperaturzaehler == 0) {
    Temperatur_check();
  }
}

void Temperatur_check() {
  if (MAX_TEMP_AKKU_RUN <= Temperatur_Akku_Max || MAX_TEMP_MOTOR <= Temperatur_Motor || MAX_TEMP_LEISTUNGSELEKTRONIK <= Temperatur_Leistungselektronik_Max) { //wenn True dann Überhitzt
    if (Uebertemperatur_Zaehler >= Uebertemperatur_Zaehler_Speicher) {
      Uebertemperatur = true;
    }
  }
  else if (MAX_TEMP_AKKU_STARTUP - 5 > Temperatur_Akku_Max && MAX_TEMP_MOTOR - 20 > Temperatur_Motor && MAX_TEMP_LEISTUNGSELEKTRONIK - 20 > Temperatur_Leistungselektronik_Max) { //wenn True dann um 10 bzw. 20 Grad runter gekühlt
    Uebertemperatur = false;
    Uebertemperatur_Zaehler = 0;
  }

  //ab hier wird die Untertemperatur ausgelesen
  if (Temperatur_Akku_Min <= MIN_TEMP_AKKU && Temperatur_Akku_Min > -127) {
    Untertemperatur_Zaehler++;
    if (Untertemperatur_Zaehler >= Untertemperatur_Zaehler_Speicher) {
      Untertemperatur = true;
    }
  }
  else if (Temperatur_Akku_Min > MIN_TEMP_AKKU) {
    Untertemperatur = false;
    Untertemperatur_Zaehler = 0;
  }
  //ab hier Temperatursensorfehler überprüfen
  if (Temperatur_Akku_Min == -127 || Temperatur_Leistungselektronik_Min == -127 || Temperatur_Motor == -127) {
    Temperatursensor_Fehler_Zaehler++;
    if (Temperatursensor_Fehler_Zaehler >= Temperatursensor_Fehler_Zaehler_Speicher) {
      Temperatursensor_Fehler = true;
    }
  }
  else {
    Temperatursensor_Fehler = false;
    Temperatursensor_Fehler_Zaehler = 0;
  }
  Freigabe_Check(); //am Ende wird die Freigabe überprüft
}


void Temperatur_start () {
  sensors.setResolution(Temperatursensor_Akku_1, 9);
  sensors.setResolution(Temperatursensor_Akku_2, 9);
  sensors.setResolution(Temperatursensor_Akku_3, 9);
  sensors.setResolution(Temperatursensor_Akku_4, 9);
  sensors.setResolution(Temperatursensor_Akku_5, 9);
  sensors.setResolution(Temperatursensor_Akku_6, 9);
  sensors.setResolution(Temperatursensor_Motor, 9);
  sensors.setResolution(Temperatursensor_Leistungselektronik_1, 9);
  sensors.setResolution(Temperatursensor_Leistungselektronik_2, 9);
  //sensors.setResolution(Temperatursensor_Leistungselektronik_3, 9);
  Temperatur_Motor = sensors.getTempC(Temperatursensor_Motor);
  Temperatur_Leistungselektronik_1 = sensors.getTempC(Temperatursensor_Leistungselektronik_1);
  Temperatur_Leistungselektronik_2 = sensors.getTempC(Temperatursensor_Leistungselektronik_2);
  //Temperatur_Leistungselektronik_3 = sensors.getTempC(Temperatursensor_Leistungselektronik_3);
  Temperatur_Akku_1 = sensors.getTempC(Temperatursensor_Akku_1);
  Temperatur_Akku_2 = sensors.getTempC(Temperatursensor_Akku_2);
  Temperatur_Akku_3 = sensors.getTempC(Temperatursensor_Akku_3);
  Temperatur_Akku_4 = sensors.getTempC(Temperatursensor_Akku_4);
  Temperatur_Akku_5 = sensors.getTempC(Temperatursensor_Akku_5);
  Temperatur_Akku_6 = sensors.getTempC(Temperatursensor_Akku_6);

  Temperatur_Akku_Min = min (Temperatur_Akku_1, Temperatur_Akku_2);
  Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_3);
  Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_4);
  Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_5);
  Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_6);
  Temperatur_Akku_Max = max (Temperatur_Akku_1, Temperatur_Akku_2);
  Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_3);
  Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_4);
  Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_5);
  Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_6);
  Temperatur_Leistungselektronik_Min = min (Temperatur_Leistungselektronik_1, Temperatur_Leistungselektronik_2);
  //Temperatur_Leistungselektronik_Min = min (Temperatur_Leistungselektronik_Min, Temperatur_Leistungselektronik_3);
  Temperatur_Leistungselektronik_Max = max (Temperatur_Leistungselektronik_1, Temperatur_Leistungselektronik_2);
  Temperatur_Leistungselektronik_Max = max (Temperatur_Leistungselektronik_Max, Temperatur_Leistungselektronik_3);
  Temperatur_check();
}
