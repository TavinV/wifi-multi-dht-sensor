# Trabalho final da matéria de ARIOT
Este programa é o produto do primeiro semestre das aulas de ARIOT.

## Grupo

* Otávio V. F. de Souza
* Lucas E. S. Gomes
* Igor T. Souza
* Leonardo Porfirio


```
#include <Adafruit_SSD1306.h>
#define OLED_LARGURA 128                // Número de Pixels do display OLED (Largura)
#define OLED_ALTURA  64                 // Número de Pixels do display OLED (Altura)
#define OLED_RESET   4                  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_LARGURA, OLED_ALTURA, &Wire, OLED_RESET);//inicialização do display SSD1306
```
