const int potenciometro = A0;
const int botao = 2;
const int led = 8;

enum Estado {
  CONFIGURANDO,
  CONTANDO,
  FINALIZADO
};

Estado estadoAtual = CONFIGURANDO;

int tempoSelecionado = 1;

unsigned long tempoInicial = 0;
unsigned long ultimoEnvio = 0;

bool botaoAnterior = HIGH;

int lerPotenciometro() {
  int leitura = analogRead(potenciometro);

  return map(leitura, 0, 1023, 1, 30);
}

void iniciarContagem() {
  tempoSelecionado = lerPotenciometro();

  tempoInicial = millis();

  estadoAtual = CONTANDO;

  digitalWrite(led, LOW);

  Serial.println("Contagem iniciada!");
  Serial.print("Tempo selecionado: ");
  Serial.print(tempoSelecionado);
  Serial.println(" segundos");
}

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  Serial.begin(9600);

  digitalWrite(led, LOW);

  Serial.println("Temporizador iniciado");
  Serial.println("Ajuste o potenciometro e pressione o botao.");
}

void loop() {

  bool leituraBotao = digitalRead(botao);

  bool clique = botaoAnterior == HIGH && leituraBotao == LOW;

  botaoAnterior = leituraBotao;

  switch (estadoAtual) {

    case CONFIGURANDO:

      tempoSelecionado = lerPotenciometro();

      if (millis() - ultimoEnvio >= 500) {
        ultimoEnvio = millis();

        Serial.print("Tempo selecionado: ");
        Serial.print(tempoSelecionado);
        Serial.println(" segundos");
      }

      if (clique) {
        iniciarContagem();
      }

      break;

    case CONTANDO: {

      unsigned long decorrido = millis() - tempoInicial;
      unsigned long duracao = tempoSelecionado * 1000UL;

      if (decorrido >= duracao) {

        estadoAtual = FINALIZADO;

        digitalWrite(led, HIGH);

        Serial.println("TEMPO FINALIZADO!");
        Serial.println("LED ligado.");

      } else {

        if (millis() - ultimoEnvio >= 1000) {
          ultimoEnvio = millis();

          int restante = (duracao - decorrido + 999) / 1000;

          Serial.print("Tempo restante: ");
          Serial.print(restante);
          Serial.println(" segundos");
        }
      }

      break;
    }

    case FINALIZADO:

      if (clique) {
        estadoAtual = CONFIGURANDO;

        digitalWrite(led, LOW);

        Serial.println("Novo temporizador.");
        Serial.println("Escolha o tempo.");
      }

      break;
  }
}

