#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <DHT.h>

#define WIFI_SSID         "Coloque_Aqui_o_nome_do_seu_WiFi"
#define WIFI_PASS         "A_Senha_do_seu_WiFi"
#define APP_KEY           "Coloque aqui a chave do app, que você acha lá no site do Sinric Pro"
#define APP_SECRET        "Coloque o senha do app, está na parte de credenciais"

#define Lampada_ID        "Copie e cole aqui"
#define Lampada_Pin       5
#define BAUD_RATE         9600

#define DHT_PIN           2
#define DHT_TYPE          DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setupWiFi();
void setupSinricPro();
bool LampadaState(const String &deviceId, bool &state);
float lerTemperatura();

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro();
  pinMode(Lampada_Pin, OUTPUT);
  dht.begin();
}

void loop() {
  SinricPro.handle();
  float temperatura = lerTemperatura();
  delay(1000);
}

bool LampadaState(const String &deviceId, bool &state) {
  Serial.printf("A lampada foi %s\r\n", state ? "ligada" : "desligada");
  digitalWrite(Lampada_Pin, state);
  return true; 
}

void setupWiFi() {
  Serial.printf("\r\nConectando WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }

  Serial.printf("Conectado!\r\nEndereço de IP eh %s\r\n", WiFi.localIP().toString().c_str());
}

void setupSinricPro() {
  SinricProSwitch &mySwitch1 = SinricPro[Lampada_ID];
  mySwitch1.onPowerState(LampadaState);

  SinricPro.onConnected([]() { Serial.printf("Conectado a nuvem SinricPro\r\n"); });
  SinricPro.onDisconnected([]() { Serial.printf("Desconectado a nuvem SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

float lerTemperatura() {
  float temperatura = dht.readTemperature();

  if (isnan(temperatura)) {
    Serial.println("Falha ao ler a temperatura do sensor DHT!");
    return 0.0;
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");
    return temperatura;
  }
}
