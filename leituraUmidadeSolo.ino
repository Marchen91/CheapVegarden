void leituraUmidadeSolo() {
  HTTPClient http;
  //String requisicaoGet = "http://192.168.40.33:9000/setup/lerUmidadesETipoControle";
  String requisicaoGet = "http://192.168.0.104:9000/setup/lerUmidadesETipoControle";
  http.begin(requisicaoGet);
  int httpCode = http.GET();
  if(httpCode>0){
    delay(5000);
    requisicaoGet = http.getString();
    //char json[500];
    //response.replace(" ", "");
    //response.replace("\n", "");
    //response.trim();
    //response.remove(0,1);
    //response.toCharArray(json,500);
    //const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    DynamicJsonBuffer jsonBuffer(1024);

    // Parse JSON object
    JsonObject& root = jsonBuffer.parseObject(requisicaoGet); 
      
    //deserializeJson(doc, json);
    umiMaxiGet= root["umidadeMaxima"];
    umiMinGet = root["umidadeMinima"];
    tipoControle = root["tipoControle"];
    //statusSolenoide = root["status"];
    Serial.println("Status requisição GET : ");
    Serial.println(requisicaoGet);
    Serial.println("Valor Umidade máxima lido: ");
    Serial.println(umiMaxiGet);
    Serial.println("Valor Umidade mínima lido: ");
    Serial.println(umiMinGet);
    Serial.println("Valores Tipo de Controle lido: ");
    Serial.println(tipoControle);
    //Serial.println("Valores Status Solenóide lido: ");
    //Serial.println(statusSolenoide);
    TelnetStream.println("Status requisição GET : ");
    TelnetStream.println(requisicaoGet);
    TelnetStream.println("Valor Umidade mínima lido: ");
    TelnetStream.println(umiMinGet);
    TelnetStream.println("Valor Umidade máxima lido: ");
    TelnetStream.println(umiMaxiGet);
    TelnetStream.println("Valores Tipo de Controle lido: ");
    TelnetStream.println(tipoControle);
    //TelnetStream.println("Valores Status Solenóide lido: ");
    //TelnetStream.println(statusSolenoide);
    http.end();
  }
  else{
    Serial.println("Erro.");
    TelnetStream.println("Erro.");
    umiMaxiGet= 60;
    umiMinGet = 40;
    tipoControle = true;
    //statusSolenoide = false;
    }
  http.end();

}
