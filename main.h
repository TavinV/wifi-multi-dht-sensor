#include <Adafruit_SSD1306.h>
#define OLED_LARGURA 128                // Número de Pixels do display OLED (Largura)
#define OLED_ALTURA  64                 // Número de Pixels do display OLED (Altura)
#define OLED_RESET   4                  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_LARGURA, OLED_ALTURA, &Wire, OLED_RESET);//inicialização do display SSD1306

#define botao 15     //pino 2 fisico será renomeado para a variavel botao
boolean bot = 0;    // bot é a variavel para leitura do status do botão (acionado ou não)      
int contador = 0;   //contador é uma variavel auxiliar para realizar contagem      

void setup()                             
{              
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);//inicialização do display e endereçamendo I2C
  display.clearDisplay();                   // Limpa p display              
  comecarDisplay();
  display.setCursor(1,8);                 // coordenada coluna=1 e linha=8 para imprimir
  display.println("*****PROGRAMA PARA TESTAR O COMANDO SWITCH/CASE**********");// texto
  
  pinMode(botao,INPUT);//define variavel pino que está relacionado ao pino 2, sendo definido como entrada de dados            
  Serial.begin(9600);//inicializa a comunicação serial (para usar o MONITOR SERIAL)
  Serial.println("*****PROGRAMA PARA TESTAR O COMANDO SWITCH/CASE**********"); 
  
 
}                             
void loop()                                     
{                                             
  bot=digitalRead(botao);// faz a leitura do estado no pino 2(BOTAO) e armazena na variavel bot        
  if(bot == HIGH)        // teste "SE" para verificar se o botão foi acionado passando de 0 para 1 assim verificando a variavel bot            
    {                                            
     contador++;         //incrementa 1 na variavel contador                   
     delay(500);         //delay                    
     Serial.print("valor do contador:");//MENSAGEM DE TEXTO na mesma linha do valor da variável contador
     Serial.println(contador);//imprimir o valor da variável contador e pular uma linha 
                
         switch(contador)
           {
             case 1:caso1();break;//caso 1
             case 2:caso2();break;//caso 2
             case 3:caso3();break;//caso 3
           }
     Serial.println("saiu do case");//msg de texto
     Serial.println();//pula linha
     Serial.println("********NOVO CICLO DE CONTAGEM***************");//MENSAGEM DE TEXTO e pular linha
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
 comecarDisplay();
 display.setCursor(1,8);                 // coordenada coluna=1 e linha=8 para imprimir
 display.println("***subrotina do caso1***");// texto												                      
 Serial.println("***subrotina do caso1***");	//mensagem no monitor serial
 display.display();
}												                      

void caso2()
{
 comecarDisplay(); 
 display.setCursor(1,8);                 // coordenada coluna=1 e linha=8 para imprimir
 display.println("***subrotina do caso2***");// texto                                             
 Serial.println("***subrotina do caso2***");  //mensagem no monitor serial
 display.display();
}

void caso3()
{
 comecarDisplay();
 display.setCursor(1,8);                 // coordenada coluna=1 e linha=8 para imprimir
 display.println("***subrotina do caso3***");// texto                                             
 Serial.println("***subrotina do caso3***");  //mensagem no monitor serial
 display.display();
 contador=0;                                 //zerar a variavel contador que auxilia na contagem para voltar para o inicio
}
