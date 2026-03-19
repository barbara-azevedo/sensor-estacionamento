#include <LiquidCrystal.h>

// Definição de pinos
#define verde A5
#define amarelo 6
#define vermelho 10
#define buzzer 9
#define trigger 13
#define echo 7
#define botao 2

LiquidCrystal lcd(12, 11, 5, 4, 3, 8);

// Variáveis
float tempo;
float distancia;
volatile int estado = LOW;
unsigned long x = 0;

// ---------------------- SETUP ----------------------
void setup() {
  pinMode(verde, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(botao, INPUT_PULLUP);

  digitalWrite(trigger, LOW);

  lcd.begin(16, 2);
  lcd.print("Sistema Pronto");

  x = millis();

  attachInterrupt(digitalPinToInterrupt(botao), rup, RISING);
}

// ---------------------- LOOP ----------------------
void loop() {

  if (estado == HIGH) {

    if ((millis() - x) > 500) {

      digitalWrite(trigger, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger, LOW);

      tempo = pulseIn(echo, HIGH);
      distancia = tempo * 0.034 / 2;

      x = millis();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dist: ");
      lcd.print(distancia);
      lcd.print(" cm");
    }

    // -------- Lógica de distância --------

    if (distancia > 90) {
      digitalWrite(verde, HIGH);
      digitalWrite(amarelo, LOW);
      digitalWrite(vermelho, LOW);
      noTone(buzzer);

      lcd.setCursor(0, 1);
      lcd.print("Area Livre       ");
    }

    else if (distancia > 60) {
      digitalWrite(verde, LOW);
      digitalWrite(amarelo, HIGH);
      digitalWrite(vermelho, LOW);
      tone(buzzer, 262);

      lcd.setCursor(0, 1);
      lcd.print("Aproximacao Segura");
    }

    else if (distancia > 40) {
      digitalWrite(verde, LOW);
      digitalWrite(amarelo, HIGH);
      digitalWrite(vermelho, LOW);
      tone(buzzer, 330);

      lcd.setCursor(0, 1);
      lcd.print("Reducao de Espaco");
    }

    else if (distancia > 20) {
      digitalWrite(verde, LOW);
      digitalWrite(amarelo, LOW);
      digitalWrite(vermelho, HIGH);
      tone(buzzer, 349);

      lcd.setCursor(0, 1);
      lcd.print("Atencao Proxima  ");
    }

    else if (distancia > 10) {
      digitalWrite(verde, LOW);
      digitalWrite(amarelo, LOW);
      digitalWrite(vermelho, HIGH);
      tone(buzzer, 392);

      lcd.setCursor(0, 1);
      lcd.print("Risco de Colisao ");
    }

    else if (distancia > 5) {
      digitalWrite(verde, LOW);
      digitalWrite(amarelo, LOW);
      digitalWrite(vermelho, HIGH);
      tone(buzzer, 450);

      lcd.setCursor(0, 1);
      lcd.print("Distancia Critica");
    }

    else {
      digitalWrite(verde, HIGH);
      digitalWrite(amarelo, HIGH);
      digitalWrite(vermelho, HIGH);
      tone(buzzer, 600);

      lcd.setCursor(0, 1);
      lcd.print("COLISAO IMINENTE ");
    }
  }

  else {
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, LOW);
    noTone(buzzer);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sistema Inativo  ");
  }
}

// ---------------------- INTERRUPÇÃO ----------------------
void rup() {
  static unsigned long last = 0;

  if (millis() - last > 200) { // debounce
    estado = !estado;
    last = millis();
  }
}
