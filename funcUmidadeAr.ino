void verificarUmidadeAr(){

  Serial.println("Executando função DHT");
  TelnetStream.println("Executando função DHT");


  // Leitura dos valores de umidades e temperaturas do DHT11
  umidadeDHT = dht.readHumidity();
  temperaturaDHT = dht.readTemperature();

  //Função apra identificar falhas na leitura do DHT11
  if (isnan(umidadeDHT) || isnan(temperaturaDHT)) 
  {
    Serial.println("Falha na leitura do DHT");
    TelnetStream.println("Falha na leitura do DHT");
    umidadeDHT = umidadeDHTAnterior;
    temperaturaDHT = temperaturaDHTAnterior;
  } 
  else
  {
    umidadeDHTAnterior = umidadeDHT;
    temperaturaDHTAnterior = temperaturaDHT;
    Serial.print("Umidade: ");
    Serial.print(umidadeDHT);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(temperaturaDHT);
    Serial.println(" °C");
    TelnetStream.println("Umidade");
    TelnetStream.println(umidadeDHT);
    TelnetStream.println(" %t");
    TelnetStream.println("Temperatura: ");
    TelnetStream.println(temperaturaDHT);
    TelnetStream.println(" °C");
    
  }

  //Acionar ou não a Solenóide de acordo com o % de umidade
  //if (umidadeDHT <= 30.0) {
  //  ligarSolenoide();
  //} else if (umidadeDHT >= 68.0) {
  //  desligarSolenoide();
  //}


  //Cálculo indicador Umidade Média Acumulada do Ar

  umidadeAcumuladaAr += umidadeDHT;
  temperaturaAcumuladaAr += temperaturaDHT;
  contUmidadeAcumAr++;

 

  //Verificação estado da solenoide
  //String statusSolenoide = (digitalRead(pino_Trilha1_Solenoide) == HIGH) ? "Status: Solenóide Ligada." : "Status: Solenóide Desligada.";
  //Serial.println(statusSolenoide);
  //TelnetStream.println(statusSolenoide);
  



}
