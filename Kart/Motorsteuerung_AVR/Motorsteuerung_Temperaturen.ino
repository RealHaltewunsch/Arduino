void Temperaturen () {  //bei jedem Durchlauf wird nur ein anderer Temperatursensor angesprochen, das verringert die Durchlaufzeit.
  switch (Temperaturzaehler) {
    case 0:
      //Temperatur_Motor = sensors.getTempC(Temperatursensor_Motor);
      Temperaturzaehler++;
      break;
    case 1:
      Temperatur_Akku_1 = sensors.getTempC(Temperatursensor_Akku_1);
      Temperaturzaehler++;
      break;
    case 2:
      Temperatur_Akku_2 = sensors.getTempC(Temperatursensor_Akku_2);
      Temperatur_Akku_Min = min (Temperatur_Akku_1, Temperatur_Akku_2);  //hier wird Akku_Min zurückgesetzt
      Temperatur_Akku_Max = max (Temperatur_Akku_1, Temperatur_Akku_2);  //hier wird Akku_Max zurückgesetzt
      Temperaturzaehler++;
      break;
    case 3:
      Temperatur_Akku_3 = sensors.getTempC(Temperatursensor_Akku_3);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_3);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_3);
      Temperaturzaehler++;
      break;
    case 4:
      Temperatur_Akku_4 = sensors.getTempC(Temperatursensor_Akku_4);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_4);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_4);
      Temperaturzaehler++;
      break;
    case 5:
      Temperatur_Akku_5 = sensors.getTempC(Temperatursensor_Akku_5);
      Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_5);
      Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_5);
      Temperaturzaehler++;
      break;
    case 6:
      flushReceive();
      SEND(206, 207);
      Temperatur_Leistungselektronik = sensors.getTempC(Temperatursensor_Leistungselektronik);
      byte TEMP[2];
      if (Serial.available() > 0) {
        Serial.readBytes(TEMP, 2);
      }
      Temperatur_Leistungselektronik_Max = max (Temperatur_Leistungselektronik, TEMP[0]);
      Temperatur_Leistungselektronik_Max = max (Temperatur_Leistungselektronik_Max, TEMP[1]);
      Temperatur_Leistungselektronik_Min = min (Temperatur_Leistungselektronik, TEMP[0]);
      Temperatur_Leistungselektronik_Min = min (Temperatur_Leistungselektronik_Min, TEMP[1]);
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
    Uebertemperatur = true;
  }
  else if (MAX_TEMP_AKKU_STARTUP - 5 > Temperatur_Akku_Max && MAX_TEMP_MOTOR - 20 > Temperatur_Motor && MAX_TEMP_LEISTUNGSELEKTRONIK - 10 > Temperatur_Leistungselektronik) { //wenn True dann um 10 bzw. 20 Grad runter gekühlt
    Uebertemperatur = false;
  }
  //ab hier wird die Untertemperatur ausgelesen
  if (Temperatur_Akku_Min <= Temperatur_Akku_Min) {
    Untertemperatur = true;
  }
  else  {
    Untertemperatur = false;
  }
  //ab hier Temperatursensorfehler überprüfen
  if (Temperatur_Akku_Min == -127 || Temperatur_Motor == -127 || Temperatur_Leistungselektronik_Min == -127) {
    Temperatursensor_Fehler = true;
  }
  else {
    Temperatursensor_Fehler = false;
  }

  Freigabe_Check(); //am Ende wird die Freigabe überprüft
}



void Temperatur_start () {
  flushReceive();
  SEND(HEATSINKTEMP, MAINBOARDTEMP);
  byte TEMP[2];
  sensors.setResolution(Temperatursensor_Akku_1, 9);
  sensors.setResolution(Temperatursensor_Akku_2, 9);
  sensors.setResolution(Temperatursensor_Akku_3, 9);
  sensors.setResolution(Temperatursensor_Akku_4, 9);
  sensors.setResolution(Temperatursensor_Akku_5, 9);
  //sensors.setResolution(Temperatursensor_Motor, 9);
  sensors.setResolution(Temperatursensor_Leistungselektronik, 9);
  //Temperatur_Motor = sensors.getTempC(Temperatursensor_Motor);
  Temperatur_Motor = sensors.getTempC(Temperatursensor_Leistungselektronik);
  Temperatur_Akku_1 = sensors.getTempC(Temperatursensor_Akku_1);
  Temperatur_Akku_2 = sensors.getTempC(Temperatursensor_Akku_2);
  Temperatur_Akku_3 = sensors.getTempC(Temperatursensor_Akku_3);
  Temperatur_Akku_4 = sensors.getTempC(Temperatursensor_Akku_4);
  Temperatur_Akku_5 = sensors.getTempC(Temperatursensor_Akku_5);
  Temperatur_Leistungselektronik = sensors.getTempC(Temperatursensor_Leistungselektronik);
  if (Serial.available() > 0) {
    Serial.readBytes(TEMP, 2);
  }
  Temperatur_Leistungselektronik_Max = max (Temperatur_Leistungselektronik, TEMP[0]);
  Temperatur_Leistungselektronik_Max = max (Temperatur_Leistungselektronik_Max, TEMP[1]);
  Temperatur_Leistungselektronik_Min = min (Temperatur_Leistungselektronik, TEMP[0]);
  Temperatur_Leistungselektronik_Min = min (Temperatur_Leistungselektronik_Min, TEMP[1]);
  Temperatur_Akku_Min = min (Temperatur_Akku_1, Temperatur_Akku_2);
  Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_3);
  Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_4);
  Temperatur_Akku_Min = min (Temperatur_Akku_Min, Temperatur_Akku_5);
  Temperatur_Akku_Max = max (Temperatur_Akku_1, Temperatur_Akku_2);
  Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_3);
  Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_4);
  Temperatur_Akku_Max = max (Temperatur_Akku_Max, Temperatur_Akku_5);
  Temperatur_check();
  /*Serial.println(Temperatur_Akku_1);
  Serial.println(Temperatur_Akku_2);
  Serial.println(Temperatur_Akku_3);
  Serial.println(Temperatur_Akku_4);
  Serial.println(Temperatur_Akku_5);
  Serial.println(Temperatur_Leistungselektronik);
  */
}
