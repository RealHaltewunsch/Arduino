void Regenerativbremsen_Auslesen () {
  Regenerativbremsen = digitalRead(Regenerativbremsen_PIN);
  digitalWrite(Regenerativbremsen_PIN_Leuchte, Regenerativbremsen);
  return;
}
