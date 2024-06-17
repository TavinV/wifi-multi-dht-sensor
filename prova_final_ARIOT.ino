#include <Adafruit_SSD1306.h>
#define OLED_LARGURA 128                // Número de Pixels do display OLED (Largura)
#define OLED_ALTURA  64                 // Número de Pixels do display OLED (Altura)
#define OLED_RESET   4                  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_LARGURA, OLED_ALTURA, &Wire, OLED_RESET);//inicialização do display SSD1306

#include <WiFi.h>
#include <WiFiMulti.h>   //  Biblioteca Inserida
WiFiMulti wifiMulti;    //Declarando um recurso para ser utilizado

const uint32_t connectTimeoutMs = 10000;

const char* rede1 = "moto g9 play";   //Criando uma varivael para redes de conexão
const char* rede2 = "Tavin Net";      //Criando uma varivael para redes de conexão

#define botao 15     //pino 15 fisico será renomeado para a variavel botao
boolean bot = 0;    // bot é a variavel para leitura do status do botão (acionado ou não)      
int contador = 1;   //contador é uma variavel auxiliar para realizar contagem      

#include <DHT.h>
DHT dht(5, DHT11); // Trocar para 11 posteriormente

#include "time.h"//inclusão a biblioteca time

const char* ntpServer = "pool.ntp.org";  //servidor a ser acessado NTP
const long  gmtOffset_sec =-10800;       //compensação GMT: GMT do Brazil é com -3horas * 3600para converter em segundos assim = -10800// Deslocamento do horário de Greenwich (GMT) em segundos (fuso horário -3 horas)
const int   daylightOffset_sec =0;       //Deslocamento de horário de verão em segundos (nenhum neste caso)//mudar para 0 pois não é aplicavel no para o Brasil


void setup()                             
{              
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);//inicialização do display e endereçamendo I2C
  
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(rede1, "tbsnzv09828"); // Aqui estamos registrando uma nova rede, com ssid e senha
  wifiMulti.addAP(rede2, "eotatasnekrl"); // Aqui estamos registrando uma nova rede, com ssid e senha
  wifiMulti.addAP("Wokwi-GUEST", ""); // Aqui estamos registrando uma nova rede, com ssid e senha

  dht.begin();
  display.clearDisplay();                 // Limpa p display 
  display.setTextSize(1.5);               // Tamanho da fonte
  display.setTextColor(WHITE);            //Cor da fonte

  display.setCursor(0,0);                 // coordenada coluna=1 e linha=8 para imprimir
  display.println("PROJETO FINAL DE IOT");// texto
  display.setCursor(0,30);
  display.println("Buscando conexão...");
  display.display();

  while (wifiMulti.run(connectTimeoutMs) != WL_CONNECTED)
    {
      delay(100);
      Serial.print(".");
    }

  display.clearDisplay();                  // Limpa p display 
  display.setTextSize(1.5);               // Tamanho da fonte
  display.setTextColor(WHITE);            // Cor da fonte
  
  display.setCursor(0,8);
  display.println("Wifi conectado!");

  display.setCursor(0,30);
  display.print(WiFi.SSID());           
  display.print(" "); 

  display.setTextSize(0.7);
  display.setCursor(0,40);
  display.println("IP : " + String(WiFi.localIP()));
  display.display();

  pinMode(botao,INPUT);//define variavel pino que está relacionado ao pino 2, sendo definido como entrada de dados            
  Serial.begin(9600);//inicializa a comunicação serial (para usar o MONITOR SERIAL)

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);// inicializa para obter o tempo
  
}                             
void loop()                                     
{                                             
  bot=digitalRead(botao);      //Leitura do Botão
  if(bot == HIGH)              //Se botão for precionado, encrementar 1                    
    {
    delay(500);                                            
    contador++;               //incrementa 1 na variavel contador                                  
    Serial.println(contador);
    switch(contador)          //Mude caso contador 
      {
        case 1:caso1();break; // informações da conexão
        case 2:caso2();break; // relogio ntp
        case 3:caso3();break; // sensor dht
      }
  }
}

void comecarDisplay()
{
  display.clearDisplay();                 // Limpa p display
  display.setTextSize(1.5);               // Tamanho da fonte
  display.setTextColor(WHITE); 
}

void caso1()                                  //nome da subrotina
{

  while (contador == 1){
    // if (WiFi.status() == WL_CONNECTED)
    if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) 
    { 
      comecarDisplay();
      display.setCursor(0,8);
      display.println("Wifi conectado!");

      display.setCursor(0,30);
      display.print(WiFi.SSID());           //imprimir nome da rede
      display.print(" "); 

      display.setTextSize(0.7);             //Tamanho da fonte = 0.7
      display.setCursor(0,40);
      display.println("IP : " + String(WiFi.localIP()));        //imprimir o IP da rede 
      display.display();

      if(digitalRead(botao) == HIGH)
      { 
        break;
      } 
    }
    else 
    {
      comecarDisplay();
      display.setCursor(0,0);
      display.println("Buscando conexão...");
      display.display();

      if(digitalRead(botao) == HIGH)
      {   
        break;
      } 
    }
  }
}                                             

void printLocalTime()                              //subrotina relogio
{                                           //inicio da subrotina
    struct tm timeinfo;                     //criação de uma struct tm chamada de timeinfo que contém todos os detalhes sobre o tempo (H:M:S DD/MM/AA)
    if(!getLocalTime(&timeinfo))            //Obtenha todos os detalhes sobre data e hora e salve na estrutura timeinfo
    {
     return;
     }                             
    display.setCursor(0,0);                  //coordenada coluna=1 e linha=8 para imprimir
    display.println("****** RELOGIO ******");//texto
    display.setTextSize(2);                  //Tamanho da fonte
    display.setCursor(15, 16);               //coordenada coluna=15 e linha=16
    display.println(&timeinfo, "%H:%M:%S");  //imprimi a struct timeinfo no formato Hora:Minuto:Segundo
    display.setTextSize(0);                  //Tamanho da fonte
    display.setCursor(30, 40);               //coordenada coluna=30 e linha=40
    display.println(&timeinfo, "%A");        //imprimi a struct timeinfo o dia da semana
    display.setCursor(20, 55);               //coordenada coluna=20 e linha=55
    display.println(&timeinfo, "%d/%B/%Y");  //imprimi a struct timeinfo no formato Dia/mes/ano
    display.display();                       //finaliza a impressão das msg no display
    delay(50);                              //delay
 }                                           //fim da subrotina

void caso2()
{
  while(contador == 2) {
   comecarDisplay();
   printLocalTime();
 
    if(digitalRead(botao) == HIGH)
    {
      Serial.println("Botão apertado!");
      break;// Caso o botão seja pressionado, o loop encerra.
    }   
    
    delay(50);
  }

}

void caso3()
{ 
  while(contador == 3)
  {
    float temp = dht.readTemperature();
    float umidade = dht.readHumidity();

    comecarDisplay();
    
    display.setCursor(10,0);                 // coordenada coluna=1 e linha=8 para imprimir
    display.println("Dados do Sensor DHT");

    display.setTextSize(0.7);               // Tamanho da fonte
    display.setCursor(0,15);
    display.println("**** Temperatura ****");
    display.setCursor(35,25);
    display.println(".");
    display.setCursor(40,30);
    display.println("C " + String(temp));
    
    display.setCursor(0,40);
    display.println("* umidade relativa *");
    display.setCursor(40,55);
    display.println(String(umidade) + "%");
    display.display();
    
  if(digitalRead(botao) == HIGH)
    {
      // Caso o botão seja pressionado, o loop encerra.
      break;
    } 
  
  delay(50);
  }
  contador=0;                                 //zerar a variavel contador que auxilia na contagem para voltar para o inicio
}
