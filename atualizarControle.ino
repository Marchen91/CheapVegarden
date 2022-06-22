void atualizarControle(){  
  if (digitalRead(pino_Trilha1_Solenoide) == HIGH) {
      solenoideTempoReal = "true";
      statusSolenoide = true;
    } else {
      solenoideTempoReal = "false";
      statusSolenoide = false;
    }
  umidadeControle = double(porcentUmidade_Trilha1);
  if(WiFi.status()== WL_CONNECTED){
   
     HTTPClient http;   
     Serial.println("Valores tabela controle: \n");
     TelnetStream.println("Valores tabela controle: ");
     //http.begin("http://192.168.40.33:9000/controle");
     http.begin("http://192.168.0.104:9000/controle");
     //http.begin("http://cheapvegarden.herokuapp.com/controle");
     http.addHeader("Content-Type", "application/json");            
   
     //int httpResponseCode = http.PUT("PUT sent from ESP32"); 
     StaticJsonBuffer<1024> jsonBuffer;
     JsonObject &root = jsonBuffer.createObject();
     Serial.println("Status da Solenoide:  \n");
     Serial.println(statusSolenoide);
     if(statusSolenoide==0 || statusSolenoide==false ){
        statusControleSolenoide = "false";
        Serial.println("Status  Controle Solenoide  FALSE:  \n");
        Serial.println(statusControleSolenoide);
      }
    else{
        statusControleSolenoide = "true";
        Serial.println("Status  Controle Solenoide  TRUE:  \n");
        Serial.println(statusControleSolenoide);
        }
          
     root["statusSolenoide"] = String(statusControleSolenoide);     
     root["temperaturaClima"] = String(temperaturaDHT);
     root["umidadeClima"] = String(umidadeDHT);
     root["umidadeSolo"] = String(umidadeControle);
     root.printTo(Serial);
     
     TelnetStream.println(Serial);
          /*int httpResponseCode = http.POST("{\n\t\"id\":\"urn:ngsi-ld:Sensor:001\", \"type\":\"MotionSensor\",\n\t\"value\":\"NO\"\n}"); */
     char json_str[1024];
     root.prettyPrintTo(json_str, sizeof(json_str));
     
     int httpResponseCode = http.PUT(json_str); 
  
  
  
  
       
   
     if(httpResponseCode>0){
   
      String response = http.getString();   
      Serial.println("\n");
      Serial.println("Código de status Controle :");
      Serial.println(httpResponseCode);
      Serial.println(response);    
      TelnetStream.println("\n");
      TelnetStream.println("Código de status Controle :");
      TelnetStream.println(httpResponseCode);
      TelnetStream.println("response");
  
     }else{
   
      Serial.print("Error on sending PUT Request: ");
      Serial.println(httpResponseCode);
      

      TelnetStream.println("Error on sending PUT Request: ");
      TelnetStream.println(httpResponseCode);
   
     }
   
     http.end();
   
   }else{
      Serial.println("Error in WiFi connection");
   }
   
    delay(10000);
 }
