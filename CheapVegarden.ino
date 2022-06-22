
// RemoteXY select connection mode and include library
//#define REMOTEXY_MODE__ESP32CORE_WIFI_POINT

#include <WiFi.h>
//#include <RemoteXY.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//OTA e Telnet Stream
#include <TelnetStream.h>
#include <WiFi.h> 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>



// RemoteXY connection settings
//#define REMOTEXY_WIFI_SSID "Fatec Lab_IoT"
//#define REMOTEXY_WIFI_PASSWORD "%fatecrp!"
const char* host = "CheapVegarden";
const char* ssid = "CheapVegarden"; /* coloque aqui o nome da rede wi-fi que o ESP32 deve se conectar */
const char* password = "@123Cheap";
//
//IPAddress local_IP(192, 168, 0, 103);
//IPAddress gateway(192, 168, 40, 2);
//IPAddress subnet(255, 255, 255, 0);
//IPAddress primaryDNS(192, 168, 40, 3); //optional
//IPAddress secondaryDNS(8, 8, 4, 4); //optional




#define pino_Trilha1_SensorUmidade 36
#define pino_Trilha1_Solenoide 14
#define pino_Trilha1_SensorVolumetriaAgua 39
#define DHTPIN 13
#define DHTTYPE DHT22
//***************************************************

//* * Variáveis de Configuração das Trilhas de Irrigação da Horta Automatizada * *

//Observação: Cada trilha será equivalente a um canteiro de plantio.
int valorUmidade_Trilha1 = 0;
int vetorValorUmidadeTrilha1[10];
int porcentUmidade_Trilha1 = 0.0; //Valores em porcentagem de 0% a 100%
float litrosPorMinuto_Trilha1 = 0.0;
boolean estadoIrrigacao_Trilha1 = false;
float fluxoAcumulado = 0.0;
float volumeAcumulado = 0.0;
float contFluxoAcum = 0;
float umidadeAcumulada = 0.0;
float contUmidadeAcum = 0;
float umidadeAcumuladaAr = 0.0;
float temperaturaAcumuladaAr = 0.0;
float contUmidadeAcumAr = 0;
boolean irrigacaoManual = false;
boolean irrigacaoAuto = false;
unsigned long leituraIrrigando = 0;
unsigned long timeoutIrrigacaoManual = 0;
unsigned long timeoutLeituraUmidade = 0;
unsigned long timeoutLeituraVolumetriaAgua = 0;
int umiMaxiGet= 0;
int umiMinGet = 0;
boolean tipoControle= false;
boolean statusSolenoide=false;
String solenoideTempoReal= "false";
double umidadeDHT = 0.0;
double temperaturaDHT = 0.0;
double umidadeDHTAnterior = 0.0;
double temperaturaDHTAnterior = 0.0;
double umidadeControle= 0.0;
int len = 0;
float porcentagemUmidadeMedia = 0.0;
unsigned long tempoIrrigacaoMin = 0;
String statusControleSolenoide = "false";




//unsigned long timeoutTelaRemoteXY = 0;

//definicao do pino do sensor e de interrupcao
//const int INTERRUPCAO_SENSOR = 0; //interrupt = 0 equivale ao pino digital 2
//const int PINO_SENSOR = 2;

//definicao da variavel de contagem de voltas
unsigned long contador = 0;

//definicao do fator de calibracao para conversao do valor lido
const float FATOR_CALIBRACAO = 4.5;

//definicao das variaveis de fluxo e volume
float fluxo = 0;
float volume = 0;
float volume_total = 0;

//definicao da variavel de intervalo de tempo
unsigned long tempo_antes = 0;

// * * Variáveis Globais do Sistema de Controle

//***************************************************

//***************************************************
//Variáveis de Controle de Comunicação de Dados em REDE/INTERNET
unsigned long tempoEnvioLog = 0;
unsigned long timeoutWiFi = 0;
//***************************************************
byte mac[]={0x38,0xF7,0x3A,0xF5,0xFF,0x40};
/* Variáveis globais */
int contador_ms = 0;
 








DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);

void setup() {
  
  
  //Configuração para uso do Monitor Serial
  Serial.begin(115200);
//  if (!WiFi.config(local_IP, gateway, subnet,primaryDNS,secondaryDNS)) {
//    Serial.println("STA Failed to configure");
//  }
  
  Serial.println("Energizando Arduino");
  //inicializando a conexão da Rede WiFi
  conectarRedeWiFi();
  //WiFi.macAddress(mac);
    Serial.print(mac[5],HEX);
    Serial.print(":");
    Serial.print(mac[4],HEX);
    Serial.print(":");
    Serial.print(mac[3],HEX);
    Serial.print(":");
    Serial.print(mac[2],HEX);
    Serial.print(":");
    Serial.print(mac[1],HEX);
    Serial.print(":");
    Serial.println(mac[0],HEX);
  

  //Configuração dos pinos da placa Wemos_D1_R32
  pinMode(pino_Trilha1_SensorUmidade, INPUT);
  pinMode(pino_Trilha1_Solenoide, OUTPUT);
  pinMode(pino_Trilha1_SensorVolumetriaAgua, INPUT_PULLUP);

  //Configuração - Estado inicial das portas dos componentes
  desligarSolenoide();

  //O sistema inicia no estado de LIGADO (sysStatus==true)
  //sysStatus = true;
  //RemoteXY.switchOnOff = 1;

  //TIMEOUTS - Configuração
  //timeoutDadosGoogleDocs = millis() + 3600000; //1 hora em milissegundos ==> 3600000
  //timeoutLeituraUmidade = millis() + 300000;  //a cada 5 minutos

  dht.begin();
  TelnetStream.begin();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! This is a sample response.");
  });

  AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
  server.begin();
  Serial.println("HTTP server started");
  
  //Mensagem de OK do Sistema
  Serial.println("Sistema de Controle Horta Automatizada FATECRP iniciado...");
  TelnetStream.print("Sistema de Controle Horta Automatizada FATECRP iniciado...");


       
  //Serial.end();
}

//############################################################################

void loop() {

  
  
  //Atualização de dados na tela do App RemoteXY
  //updateTelaAppMovel();
  //delay(100);

  //Verificando o Status do sistema da horta automática
 // if (sysStatus == true) {
    
    verificarVolumetriaAgua();
    leituraIrrigando = lerTempoIrrigacao(); 
    if (millis() > timeoutLeituraUmidade) {
      leituraUmidadeSolo();
      verificarUmidadeSolo();
      if(tipoControle == true){
        
        irrigacaoAutomatica();
        }
      else{
        leituraTipoControle();
        irrigacaoAgendada();
        }
      verificarUmidadeAr();
      //leituraTipoControle();
      atualizarControle();
      timeoutLeituraUmidade = millis() + 5000; //5 seg
    }
    
//    if ((millis() > timeoutLeituraVolumetriaAgua)) {
//      verificarVolumetriaAgua();
//      timeoutLeituraVolumetriaAgua = millis() + 5000; //5 seg
//    }
    

    /*if (millis() > timeoutIrrigacaoManual) {
      irrigarManual();
      timeoutIrrigacaoManual = millis() + 300000; //5 minutos
    }*/

    //delay(100);

    //Envio de dados para planilha em nuvem de 1 em 1 hora
    if (millis() > tempoEnvioLog) {
      verificarUmidadeAr();
      Serial.println( temperaturaDHT);
      TelnetStream.print(temperaturaDHT);
     
      enviarLog();
      
      //timeoutDadosGoogleDocs = millis() + 30000;
    }

    


    
   
  /*} else {
    desligarSolenoide();
    Serial.println("Sistema hortamática desativado manualmente...");
  }*/
} //end-loop
