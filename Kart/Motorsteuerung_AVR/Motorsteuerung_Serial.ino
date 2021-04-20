void SEND( unsigned short int command, unsigned short int value) {
  Serial.write(command);
  Serial.write(value);
}

void flushReceive() {
  while (Serial.available()) {
    Serial.read();
  }
}
