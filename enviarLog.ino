void enviarLog() {

if (WiFi.status() == WL_CONNECTED)
    {
//        int mediaFluxoAcum = (int)(fluxoAcumulado / contFluxoAcum);
//        int mediaUmidadeSolo = (int)(umidadeAcumulada / contUmidadeAcum);
//        int mediaUmidadeAr = (int)(umidadeAcumuladaAr / contUmidadeAcumAr);
//        int mediaTemperaturaAr = (int)(temperaturaAcumuladaAr / contUmidadeAcumAr);

          
        double mediaFluxoAcum = (fluxoAcumulado / contFluxoAcum);
        double mediaUmidadeSolo = (umidadeAcumulada / contUmidadeAcum);
        double mediaUmidadeAr = (umidadeAcumuladaAr / contUmidadeAcumAr);
        int mediaTemperaturaAr = (int)(temperaturaAcumuladaAr / contUmidadeAcumAr);
        if(mediaFluxoAcum >=0){
          
            mediaFluxoAcum = mediaFluxoAcum;
          
          
          
          }
         else{
            mediaFluxoAcum = 0;
          
          }
          
//        Serial.println("Valores Umidade acumulada: \n");        
//        Serial.println(umidadeAcumulada);
//        Serial.println("Valores Contador Umidade acumulada: \n");        
//        Serial.println(contUmidadeAcum);
//        TelnetStream.print("Valores Umidade acumulada: \n");
//        TelnetStream.print(umidadeAcumulada);
//        TelnetStream.print("Valores Contador Umidade acumulada: \n");
//        TelnetStream.print(contUmidadeAcum);




        
        HTTPClient http;
        Serial.println("Valores tabela log: \n");
        TelnetStream.print("Valores tabela log: \n");
        //http.begin("http://192.168.40.33:9000/log"); 
        http.begin("http://192.168.0.104:9000/log"); 
        //http.begin("http://cheapvegarden.herokuapp.com/log"); 

        
        http.addHeader("Content-Type", "application/json");

        StaticJsonBuffer<1024> jsonBuffer;
        JsonObject &root = jsonBuffer.createObject();

        root["fluxo"] = String(mediaFluxoAcum);
        root["temperaturaClima"] = String(mediaTemperaturaAr);
        root["umidadeClima"] = String(mediaUmidadeAr);
        root["umidadeSolo"] = String(mediaUmidadeSolo);

        
        
//        root["fluxo"] = "12.02";
//        root["temperaturaClima"] = String(mediaTemperaturaAr);
//        root["umidadeClima"] = String(umidadeDHT);
//        root["umidadeSolo"] = String(umidadeControle);
        root.printTo(Serial);
        TelnetStream.print(Serial);
        /*int httpResponseCode = http.POST("{\n\t\"id\":\"urn:ngsi-ld:Sensor:001\", \"type\":\"MotionSensor\",\n\t\"value\":\"NO\"\n}"); */
        char json_str[1024];
        root.prettyPrintTo(json_str, sizeof(json_str));
        int httpResponseCode = http.POST(json_str);
        if (httpResponseCode > 0)
        {
            String response = http.getString();
            Serial.println("\n");
            Serial.println("Código de Status Log: \n");
            Serial.println(httpResponseCode);
            Serial.println(response);
            TelnetStream.print("Codigo de Status de Log:\n");
            TelnetStream.print(httpResponseCode);
            TelnetStream.print(response);
        }
        else
        {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
            TelnetStream.print("Error no envio do log: ");
            TelnetStream.print(httpResponseCode);
            
        }
        http.end();

       
    }
    else
    {
        Serial.println("Error in WiFi connection");
    }
delay(1000);
//tempoEnvioLog = millis() + 3600000; //1 hora
tempoEnvioLog = millis() + 360000; //1 hora
umidadeAcumulada =0;
contUmidadeAcum =0;
umidadeAcumuladaAr = 0;
temperaturaAcumuladaAr = 0;
contUmidadeAcumAr =0;


  
}
