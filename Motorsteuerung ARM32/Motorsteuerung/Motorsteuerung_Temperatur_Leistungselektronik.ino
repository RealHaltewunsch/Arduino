int Max_Leistungselektronik_Temperatur_erfragen () {
  sensors.requestTemperatures(); // Send the command to get temperatures
  Temperatur_Leistungselektronik_1 = sensors.getTempC(Temperatursensor_Leistungselektronik_1);
  Temperatur_Leistungselektronik_2 = sensors.getTempC(Temperatursensor_Leistungselektronik_2);
  Temperatur_Leistungselektronik_Max = max (Temperatur_Leistungselektronik_1, Temperatur_Leistungselektronik_2);
  return Temperatur_Leistungselektronik_Max;
}

int Min_Leistungselektronik_Temperatur_erfragen () {
  sensors.requestTemperatures(); // Send the command to get temperatures
  Temperatur_Leistungselektronik_1 = sensors.getTempC(Temperatursensor_Leistungselektronik_1);
  Temperatur_Leistungselektronik_2 = sensors.getTempC(Temperatursensor_Leistungselektronik_2);
  Temperatur_Leistungselektronik_Max = min (Temperatur_Leistungselektronik_1, Temperatur_Leistungselektronik_2);
  return Temperatur_Leistungselektronik_Min;
}
