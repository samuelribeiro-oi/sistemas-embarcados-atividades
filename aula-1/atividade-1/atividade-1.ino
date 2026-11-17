const int LED_VERMELHO = 8;
const int LED_AMARELO = 9;
const int LED_VERDE = 10;

const int BOTAO = 2;

enum Estado {
  VERMELHO,
  VERDE,
  AMARELO
};

Estado estadoAtual = VERMELHO;

int leituraAnterior = HIGH;

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  pinMode(BOTAO, INPUT_PULLUP);

  Serial.begin(9600);

  atualizarSemaforo();
}

void loop() {
  int leituraAtual = digitalRead(BOTAO);

  if (leituraAnterior == HIGH && leituraAtual == LOW) {

    switch (estadoAtual) {

      case VERMELHO:
        estadoAtual = VERDE;
        break;

      case VERDE:
        estadoAtual = AMARELO;
        break;

      case AMARELO:
        estadoAtual = VERMELHO;
        break;
    }

    atualizarSemaforo();

    delay(200); 
  }

  leituraAnterior = leituraAtual;
}

void atualizarSemaforo() {

  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE, LOW);

  switch (estadoAtual) {

    case VERMELHO:
      digitalWrite(LED_VERMELHO, HIGH);
      Serial.println("VERMELHO");
      break;

    case VERDE:
      digitalWrite(LED_VERDE, HIGH);
      Serial.println("VERDE");
      break;

    case AMARELO:
      digitalWrite(LED_AMARELO, HIGH);
      Serial.println("AMARELO");
      break;
  }
}
