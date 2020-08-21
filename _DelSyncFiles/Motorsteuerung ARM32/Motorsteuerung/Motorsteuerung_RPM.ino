float Geschwindigkeit_ausgeben () {
  //noInterrupts();
  float Geschwindigkeit = 3.6 * rev * ReifenxPI / (millis() - measureTime); //Möglicherweise ungenau, Nachkommastellen!
  //uint32_t rpm = rev * 60000 / (millis() - measureTime);
  rev = 0;
  //interrupts();
  measureTime = millis();
  return Geschwindigkeit;
}

void eineUmdrehung() {
  rev++;
}
