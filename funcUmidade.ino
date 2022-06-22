void verificarUmidadeSolo()
{
  //Serial.println("#############################################");
  Serial.println("Executando função: verificarUmidadeSolo()");
  TelnetStream.println("Executando função: verificarUmidadeSolo()");
  //Sensor antigo -------------------------------------------------
  //Range analógico de leitura - 0 (mínimo) até 4095 (máximo)
  //Range de porcentagem de umidade: 550 -> 0% e 4095 -> 100%
  //---------------------------------------------------------------
  //Novo sensor HD-38
  //Range analógico de leitura - 0 (máximo) até 4095 (mínimo)
  //Range de porcentagem de umidade: 1326 (100% úmido) e 4095 (0% seco) 
  
  valorUmidade_Trilha1 = analogRead(pino_Trilha1_SensorUmidade);
  Serial.printf("Analog Read - Sensor Umidade Leitura Analógica:  %d \n", valorUmidade_Trilha1);
  TelnetStream.printf("Analog Read - Sensor Umidade Leitura Analógica:  %d \n", valorUmidade_Trilha1);
  
  //Verificação Porcentagem de Umidade
  if (valorUmidade_Trilha1 >= 2000 && valorUmidade_Trilha1 <= 4095 ) {
    porcentUmidade_Trilha1 = map(valorUmidade_Trilha1, 4095, 1500, 0, 100);
  } else {
    porcentUmidade_Trilha1 = 100.0;
  }
  Serial.printf("Porcentagem de Umidade: %d \n ", porcentUmidade_Trilha1);
  Serial.println("%  \n");
  TelnetStream.printf("Porcentagem de Umidade: %d \n ", porcentUmidade_Trilha1);
  TelnetStream.printf("%  \n");


  if(len<10){
    vetorValorUmidadeTrilha1 [len]= porcentUmidade_Trilha1;
    len++;
    umiMaxiGet= 10;
    umiMinGet = 0;
    porcentagemUmidadeMedia = 10;
    }
  else{
    
    int resto = len%10;
    int total = 0;
    
    vetorValorUmidadeTrilha1[resto]= porcentUmidade_Trilha1;
    porcentagemUmidadeMedia = 0.0;
    for (int i2 = 0; i2<10; i2++){

          total += vetorValorUmidadeTrilha1[i2];
    }

    porcentagemUmidadeMedia = total/10;
    len++;    
    //Serial.print("valor total : ");
    //Serial.print(total);
    //TelnetStream.println("valor total : ");
    //TelnetStream.println(total);
    //vetor com 10 leituras
    //umidadeMiniaMedia= //media vetor umiMinima -----valores que serao usados no if else comparativo
    //umidadeMaximaMedia= //media vetor umMaxima
    }

 
  Serial.print("Porcentagem Média : : ");
  Serial.print(porcentagemUmidadeMedia);
  Serial.print("% \n");
  TelnetStream.println("Porcentagem Média : ");
  TelnetStream.println(porcentagemUmidadeMedia);
  TelnetStream.println(" % \n");

  
}
