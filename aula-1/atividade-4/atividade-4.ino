const int botaoIniciar = 2;
const int botaoFinalizar = 3;

const int ledVermelho = 8;
const int ledAmarelo = 9;
const int ledVerde = 10;

enum Estado {
  AGUARDANDO,
  ATENDENDO,
  FINALIZADO
};

Estado estado = AGUARDANDO;

int anteriorIniciar = HIGH;
int anteriorFinalizar = HIGH;

void setup() {

  pinMode(botaoIniciar, INPUT_PULLUP);
  pinMode(botaoFinalizar, INPUT_PULLUP);

  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  Serial.begin(9600);

  Serial.println("iniciado: AGUARDANDO");

  atualizarPainel();
}

void loop() {

  int leituraIniciar = digitalRead(botaoIniciar);
  int leituraFinalizar = digitalRead(botaoFinalizar);

  if (leituraIniciar == LOW &&
      anteriorIniciar == HIGH &&
      estado == AGUARDANDO) {

    estado = ATENDENDO;

    Serial.println("AGUARDANDO -> ATENDENDO");

    atualizarPainel();

    delay(200);
  }

  if (leituraFinalizar == LOW &&
      anteriorFinalizar == HIGH &&
      estado == ATENDENDO) {

    estado = FINALIZADO;

    Serial.println("ATENDENDO -> FINALIZADO");

    atualizarPainel();

    delay(200);
  }

  if (estado == FINALIZADO) {

    delay(2000);

    estado = AGUARDANDO;

    Serial.println("FINALIZADO -> AGUARDANDO");

    atualizarPainel();
  }

  anteriorIniciar = leituraIniciar;
  anteriorFinalizar = leituraFinalizar;
}

void atualizarPainel() {

  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);

  if (estado == AGUARDANDO) {

    digitalWrite(ledVermelho, HIGH);

    Serial.println("Estado: AGUARDANDO");
  }

  else if (estado == ATENDENDO) {

    digitalWrite(ledAmarelo, HIGH);

    Serial.println("Estado: ATENDENDO");
  }

  else if (estado == FINALIZADO) {

    digitalWrite(ledVerde, HIGH);

    Serial.println("Estado: FINALIZADO");
  }
}

