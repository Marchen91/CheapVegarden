void ligarSolenoide() {
  digitalWrite(pino_Trilha1_Solenoide, HIGH);
  Serial.println("solenóide acaba de ser ligada! \n");
  TelnetStream.println("Solenóide acaba de ser ligada! \n");
  
  
}
