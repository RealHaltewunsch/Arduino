void Freigabe_Check() {
  if (!Bremse && Zuendung && !Uebertemperatur && !Untertemperatur && !AnalogSensorFehler && !Temperatursensor_Fehler && Gaspedal_angeschlossen) {
    Freigabe = true;
    Serial1.write(0x8A);    //Direction
    Serial1.write(0x01);    // FORWARD
    
  }
  else {
    Freigabe = false;
    Serial1.write(0x8A);    //Direction
    Serial1.write(0x00);    // STOP
  }
  MotorSteuerung();

  digitalWrite(Freigabe_PIN_Leuchte, Freigabe);
  digitalWrite(Enable_Pin, !Freigabe);
}
