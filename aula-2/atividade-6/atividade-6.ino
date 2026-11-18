const int sensor = A0;

const int ledVerde = 8;
const int ledAmarelo = 9;
const int ledVermelho = 10;
const int buzzer = 11;

enum Estado {
  NORMAL,
  ATENCAO,
  ALERTA
};

Estado estadoAtual = NORMAL;

int lerSensor() {
  return analogRead(sensor);
}

float converterTemperatura(int leitura) {
  float tensao = leitura * (5.0 / 1023.0);

  float temperatura = (tensao - 0.5) * 100.0;

  return temperatura;
}

void atualizarSaidas() {

  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
  noTone(buzzer);

  switch (estadoAtual) {

    case NORMAL:
      digitalWrite(ledVerde, HIGH);
      break;

    case ATENCAO:
      digitalWrite(ledAmarelo, HIGH);
      break;

    case ALERTA:
      digitalWrite(ledVermelho, HIGH);
      tone(buzzer, 1000);
      break;
  }
}

void setup() {

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  Serial.println("Sistema de temperatura iniciado");
}

void loop() {

  int leitura = lerSensor();

  float temperatura = converterTemperatura(leitura);

  if (temperatura < 30) {
    estadoAtual = NORMAL;
  }
  else if (temperatura < 40) {
    estadoAtual = ATENCAO;
  }
  else {
    estadoAtual = ALERTA;
  }

  atualizarSaidas();

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" C | Estado: ");

  switch (estadoAtual) {

    case NORMAL:
      Serial.println("NORMAL");
      break;

    case ATENCAO:
      Serial.println("ATENCAO");
      break;

    case ALERTA:
      Serial.println("ALERTA");
      break;
  }

  delay(1000);
}
