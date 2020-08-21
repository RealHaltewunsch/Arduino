void Geschwindigkeit_berechnen () {
  //noInterrupts();
  //float Geschwindigkeit = 3.6 * rev * ReifenxPI / (millis() - measureTime); //Möglicherweise ungenau, Nachkommastellen!
  //uint32_t rpm = rev * 60000 / (millis() - measureTime);
  Geschwindigkeit_in_kmh = (3.6 * rev * ReifenxPI / (millis() - measureTime));
  rev = 0;
  //interrupts();
  measureTime = millis();
  return;
}

void eineUmdrehung() {
  rev++;
  return;
}
