# Sensor de Estacionamento com Arduino

Projeto de um sensor de estacionamento utilizando Arduino, com feedback visual (LEDs), sonoro (buzzer) e exibição de distância em display LCD.

# Descrição

Este projeto simula o funcionamento de sensores de estacionamento automotivos, utilizando um sensor ultrassônico para medir a distância de obstáculos.

O sistema fornece:

- Medição de distância em tempo real
- Indicação visual por LEDs (verde, amarelo e vermelho)
- Feedback sonoro progressivo com buzzer
- Exibição no display LCD 16x2
- Ativação via botão (simulando marcha ré)

# Componentes Utilizados

- Arduino (UNO, Nano ou similar)
- Sensor ultrassônico HC-SR04
- Display LCD 16x2
- 3 LEDs (verde, amarelo e vermelho)
- Buzzer
- Botão
- Resistores (para LEDs e botão)
- Protoboard e jumpers

# Ligações
Componente	Pino Arduino
LED Verde	        A5
LED Amarelo	      6
LED Vermelho	    10
Buzzer	          9
Trigger (HC-SR04)	13
Echo (HC-SR04)	  7
Botão	            2
LCD	              12, 11, 5, 4, 3, 8

O botão está configurado com INPUT_PULLUP

# Funcionamento

O sistema inicia desligado
Ao pressionar o botão, o modo "ré" é ativado
O sensor ultrassônico começa a medir a distância
O sistema responde conforme a proximidade:

Distância	Ação
```bash
> 90 cm	Área livre (LED verde)
60–90 cm	Aproximação segura
40–60 cm	Redução de espaço
20–40 cm	Atenção
10–20 cm	Risco de colisão
5–10 cm	Distância crítica
< 5 cm	Colisão iminente
```
A frequência do buzzer aumenta conforme o obstáculo se aproxima, simulando sensores reais de estacionamento.

**Interface LCD**

Linha 1: distância medida

Linha 2: status do sistema

Exemplo:

Dist: 45 cm
Reducao de Espaco
