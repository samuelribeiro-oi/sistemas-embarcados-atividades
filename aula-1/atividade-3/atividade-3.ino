#include <Servo.h>

Servo cancela;

const int botao = 2;
const int pinoServo = 9;

enum Estado {
  FECHADA,
  ABRINDO,
  ABERTA,
  FECHANDO
};

Estado estado = FECHADA;

unsigned long tempoInicial = 0;

const unsigned long tempoMovimento = 1000;
const unsigned long tempoAberta = 3000;

int leituraAnterior = HIGH;

void setup() {
  pinMode(botao, INPUT_PULLUP);

  cancela.attach(pinoServo);

  cancela.write(0);

  Serial.begin(9600);

  Serial.println("FECHADA");
}

void loop() {

  int leitura = digitalRead(botao);

  if (estado == FECHADA &&
      leitura == LOW &&
      leituraAnterior == HIGH) {

    estado = ABRINDO;

    cancela.write(90);

    tempoInicial = millis();

    Serial.println("FECHADA -> ABRINDO");

    delay(50);
  }

  leituraAnterior = leitura;

  if (estado == ABRINDO) {

    if (millis() - tempoInicial >= tempoMovimento) {

      estado = ABERTA;

      tempoInicial = millis();

      Serial.println("ABRINDO -> ABERTA");
    }
  }

  else if (estado == ABERTA) {

    if (millis() - tempoInicial >= tempoAberta) {

      estado = FECHANDO;

      cancela.write(0);

      tempoInicial = millis();

      Serial.println("ABERTA -> FECHANDO");
    }
  }

  else if (estado == FECHANDO) {

    if (millis() - tempoInicial >= tempoMovimento) {

      estado = FECHADA;

      Serial.println("FECHANDO -> FECHADA");
    }
  }
}
