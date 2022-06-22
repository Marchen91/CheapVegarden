void desligarSolenoide() {
  digitalWrite(pino_Trilha1_Solenoide, LOW);
  Serial.println("solenóide acaba de ser DESligada! \n");
  TelnetStream.println("Solenóide acaba de ser DESligada! \n");
}
