int Max_Akku_Temperatur_erfragen () {
  sensors.requestTemperatures(); // Send the command to get temperatures
  Temperatur_Akkus_1 = sensors.getTempC(Temperatursensor_Akkus_1);
  Temperatur_Akkus_2 = sensors.getTempC(Temperatursensor_Akkus_2);
  Temperatur_Akkus_3 = sensors.getTempC(Temperatursensor_Akkus_3);
  int Temperatur_Akkus_temp = max (Temperatur_Akkus_1, Temperatur_Akkus_2);
  Temperatur_Akkus_Max = max (Temperatur_Akkus_temp, Temperatur_Akkus_3);
  return Temperatur_Akkus_Max;
}

int Min_Akku_Temperatur_erfragen () {
  sensors.requestTemperatures(); // Send the command to get temperatures
  Temperatur_Akkus_1 = sensors.getTempC(Temperatursensor_Akkus_1);
  Temperatur_Akkus_2 = sensors.getTempC(Temperatursensor_Akkus_2);
  Temperatur_Akkus_3 = sensors.getTempC(Temperatursensor_Akkus_3);
  int Temperatur_Akkus_temp = min (Temperatur_Akkus_1, Temperatur_Akkus_2);
  Temperatur_Akkus_Min = min (Temperatur_Akkus_temp, Temperatur_Akkus_3);
  return Temperatur_Akkus_Min;
}
