const int botaoAtivar = 2;
const int botaoDeteccao = 3;
const int led = 8;
const int buzzer = 9;

const int DESATIVADO = 0;
const int ATIVADO = 1;
const int ALERTA = 2;

int estado = DESATIVADO;

int leituraAnteriorAtivar = HIGH;
int leituraAnteriorDeteccao = HIGH;

void setup() {
  pinMode(botaoAtivar, INPUT_PULLUP);
  pinMode(botaoDeteccao, INPUT_PULLUP);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  Serial.println("DESATIVADO");
}

void loop() {
  int leituraAtivar = digitalRead(botaoAtivar);
  int leituraDeteccao = digitalRead(botaoDeteccao);

  if (leituraAtivar == LOW && leituraAnteriorAtivar == HIGH) {

    if (estado == DESATIVADO) {
      estado = ATIVADO;
      Serial.println("DESATIVADO -> ATIVADO");
    }
    else {
      estado = DESATIVADO;
      Serial.println("DESATIVADO");
    }

    delay(200);
  }

  if (leituraDeteccao == LOW &&
      leituraAnteriorDeteccao == HIGH) {

    if (estado == ATIVADO) {
      estado = ALERTA;
      Serial.println(" ATIVADO -> ALERTA");
    }

    delay(200);
  }

  if (estado == DESATIVADO) {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }

  else if (estado == ATIVADO) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, LOW);
  }

  else if (estado == ALERTA) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
  }

  leituraAnteriorAtivar = leituraAtivar;
  leituraAnteriorDeteccao = leituraDeteccao;
}
