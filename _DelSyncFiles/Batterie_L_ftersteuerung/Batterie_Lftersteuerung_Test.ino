void Testfunktion () {
  Serial.begin(9600);
  Serial.print("Funktion Maximale Akkutemperatur");
  Serial.println(Max_Akku_Temperatur_erfragen());
  Serial.print("Funktion Minimale Akkutemperatur");
  Serial.println(Min_Akku_Temperatur_erfragen());
  Serial.print("Zustand MOSFET");
  Serial.println(digitalRead(MOSFET));
  Serial.print("Wert Lüfter");
  Serial.println(Sollwert);
  Serial.end();
}
