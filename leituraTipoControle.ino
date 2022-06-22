void leituraTipoControle() {
  HTTPClient http;
  //String requisicaoGet = "http://192.168.40.33:9000/controle/lerStatusSolenoide";
  String requisicaoGet = "http://192.168.0.104:9000/controle/lerStatusSolenoide";
  http.begin(requisicaoGet);
  int httpCode = http.GET();
  if(httpCode>0){
    delay(5000);
    requisicaoGet = http.getString();
    Serial.println("Leitura RESPONSE  :\n");
    Serial.println(requisicaoGet);
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
    //statusSolenoide= root["statusSolenoide"];
    if(requisicaoGet=="false"){
    statusSolenoide=false;
    }
    else{
      statusSolenoide=true;}
    Serial.println("Status da Solenoide:  \n");
    Serial.println(statusSolenoide);
    

    TelnetStream.println("Status da Solenoide:  \n");
    TelnetStream.println(statusSolenoide);
    
    http.end();
  }
  else{
    Serial.println("Erro.");
    TelnetStream.println("Erro.");
    statusSolenoide = false;
    }
  http.end();

}
