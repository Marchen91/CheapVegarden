void irrigacaoAutomatica() {

if ((porcentagemUmidadeMedia <= umiMinGet) && (millis() > tempoIrrigacaoMin) ) {
    //Serial.printf(" LIGOU IRRIGAÇÃO ");
    //TelnetStream.printf(" LIGOU IRRIGAÇÃO ");
    //desligarSolenoide();
    ligarSolenoide();
    irrigacaoAuto = true;
    tempoIrrigacaoMin = millis() + 60000;
    //delay 500milis
    
  } else if ((porcentagemUmidadeMedia >= umiMaxiGet) && (millis() > tempoIrrigacaoMin)) {
    //ligarSolenoide();
    desligarSolenoide();
    irrigacaoAuto = false;
    tempoIrrigacaoMin = millis() + 6000;
  }
  Serial.print("Valor tempo mínimo de irrigação : ");
  Serial.print(tempoIrrigacaoMin);
  Serial.print("\n");
  TelnetStream.println("Valor tempo mínimo de irrigação : ");
  TelnetStream.println(tempoIrrigacaoMin);
  TelnetStream.println("\n");

  //  if (valorUmidade_Trilha1 >= 550) {
  //    Serial.println("Estado da Terra: Solo úmido.");
  //    desligarSolenoide();
  //  }
  //  else
  //  {
  //    Serial.println("Estado da Terra: Solo seco.");
  //    ligarSolenoide();
  //  }

  //Cálculo indicador Umidade Média Acumulada do Solo
  umidadeAcumulada += porcentUmidade_Trilha1;
  contUmidadeAcum++;
  Serial.print("Umidade minima comparativa: ");
  Serial.print(umiMinGet);
  Serial.print("\n");
  Serial.print("Umidade máxima comparativa: ");
  Serial.print(umiMaxiGet);
  Serial.print("\n");
  TelnetStream.println("Umidade minima comparativa: ");
  TelnetStream.println(umiMinGet);
  TelnetStream.println("\n");
  TelnetStream.println("Umidade máxima comparativa: ");
  TelnetStream.println(umiMaxiGet);
  TelnetStream.println("\n");





  
  //Verificação estado da solenoide
  String statusSolenoide = (digitalRead(pino_Trilha1_Solenoide) == HIGH) ? "Status: Solenóide Ligada." : "Status: Solenóide Desligada.";
  Serial.println(statusSolenoide);
  TelnetStream.println("Status da Solenoide");
  TelnetStream.println(statusSolenoide);
  TelnetStream.println("\n");
 
  //Serial.println("#############################################");


}
