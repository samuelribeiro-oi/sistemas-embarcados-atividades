const int botao = 2;
const int ledVerde = 8;
const int ledVermelho = 9;

enum Estado {
  BLOQUEADO,
  LIBERADO,
  ENCERRANDO
};

Estado estadoAtual = BLOQUEADO;

unsigned long tempoInicial = 0;
const unsigned long tempoAcesso = 3000;

bool botaoAnterior = HIGH;

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  Serial.begin(9600);

  Serial.println("Sistema iniciado");
  Serial.println("Estado: BLOQUEADO");
}

void loop() {
  bool leituraBotao = digitalRead(botao);

  if (botaoAnterior == HIGH && leituraBotao == LOW) {

    if (estadoAtual == BLOQUEADO) {
      estadoAtual = LIBERADO;
      tempoInicial = millis();

      Serial.println("Acesso LIBERADO!");
    }
  }

  botaoAnterior = leituraBotao;

  if (estadoAtual == LIBERADO) {

    if (millis() - tempoInicial >= tempoAcesso) {
      estadoAtual = ENCERRANDO;

      Serial.println("ENCERRANDO acesso...");
    }
  }

  switch (estadoAtual) {

    case BLOQUEADO:
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, HIGH);
      break;

    case LIBERADO:
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledVermelho, LOW);
      break;

    case ENCERRANDO:
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, HIGH);

      estadoAtual = BLOQUEADO;

      Serial.println("Acesso BLOQUEADO!");
      break;
  }
}

