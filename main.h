#include <Adafruit_SSD1306.h>
#define OLED_LARGURA 128                // Número de Pixels do display OLED (Largura)
#define OLED_ALTURA  64                 // Número de Pixels do display OLED (Altura)
#define OLED_RESET   4                  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_LARGURA, OLED_ALTURA, &Wire, OLED_RESET);//inicialização do display SSD1306

#include <WiFi.h>
#include <WiFiMulti.h>   //  Biblioteca Inserida
WiFiMulti wifiMulti;    //Declarando um recurso para ser utilizado

const uint32_t connectTimeoutMs = 10000;

const char* rede1 = "moto g9 play";
const char* rede2 = "Tavin Net";

#define botao 15     //pino 15 fisico será renomeado para a variavel botao
boolean bot = 0;    // bot é a variavel para leitura do status do botão (acionado ou não)      
int contador = 1;   //contador é uma variavel auxiliar para realizar contagem      

#include <DHT.h>
DHT dht(5, DHT22); // Trocar para 11 posteriormente

void setup()                             
{              
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);//inicialização do display e endereçamendo I2C
  
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(rede1, "tbsnzv09826"); // Aqui estamos registrando uma nova rede, com ssid e senha
  wifiMulti.addAP(rede2, "eotatasnekrl"); // Aqui estamos registrando uma nova rede, com ssid e senha
  wifiMulti.addAP("Wokwi-GUEST", ""); // Aqui estamos registrando uma nova rede, com ssid e senha

  dht.begin();
  display.clearDisplay();                   // Limpa p display 
  display.setTextSize(1.5);               // Tamanho da fonte
  display.setTextColor(WHITE); 

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

  display.clearDisplay();                   // Limpa p display 
  display.setTextSize(1.5);               // Tamanho da fonte
  display.setTextColor(WHITE); 
  
  display.setCursor(0,8);
  display.println("Wifi conectado!");

  display.setCursor(0,30);
  display.print(WiFi.SSID());
  display.print(" "); 

  display.setCursor(0,40);
  display.println("IP ");
  display.print(WiFi.localIP());
  
  display.display();


  pinMode(botao,INPUT);//define variavel pino que está relacionado ao pino 2, sendo definido como entrada de dados            
  Serial.begin(9600);//inicializa a comunicação serial (para usar o MONITOR SERIAL)
 
}                             
void loop()                                     
{                                             
  bot=digitalRead(botao);      
  if(bot == HIGH)                    
    {
    delay(100);                                            
    contador++;         //incrementa 1 na variavel contador                                   
    Serial.println(contador);
    switch(contador)
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

void caso1()									                //nome da subrotina
{

  while (contador == 1){
    // if (WiFi.status() == WL_CONNECTED)
    if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) 
    { 
      comecarDisplay();
      display.setCursor(0,8);
      display.println("Wifi conectado!");

      display.setCursor(0,30);
      display.print(WiFi.SSID());
      display.print(" "); 

      display.setCursor(0,40);
      display.println("IP ");
      display.print(WiFi.localIP());
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

void caso2()
{
 comecarDisplay();
 display.setCursor(1,8);                 // coordenada coluna=1 e linha=8 para imprimir
 display.println("***subrotina do caso2***");// texto                                             
 Serial.println(contador);
 display.display();

}

void caso3()
{
  contador=0;                                 //zerar a variavel contador que auxilia na contagem para voltar para o inicio
  
  while(contador == 0)
  {
    float temp = dht.readTemperature();
    float humidade = dht.readHumidity();

    display.clearDisplay();                 // Limpa p display
    display.setTextColor(WHITE); 

    display.setTextSize(1.5);               // Tamanho da fonte
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
    display.println("* Humidade relativa *");
    display.setCursor(40,55);
    display.println(String(humidade) + "%");
    display.display();
    
  if(digitalRead(botao) == HIGH)
    {
      // Caso o botão seja pressionado, o loop encerra.
      break;
    } 
  
  delay(50);
  }
}
