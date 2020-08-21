int Motor_Temperatur_erfragen () {
  Temperatur_Motor = sensors.getTempC(Temperatursensor_Motor);
  return Temperatur_Motor;
}
