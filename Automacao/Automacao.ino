#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include "SinricProTemperaturesensor.h"
#include "DHT.h"

#define WIFI_SSID         ""
#define WIFI_PASS         ""

#define APP_KEY           "13802641-xxxx-xxxx-xxxx-ad95f374fa0a"
#define APP_SECRET        "bd1d8dad-xxxx-xxxx-xxxx-33213fd0bd26-f195ae38-xxxx-xxxx-xxxx-58688097bab8"

#define TEMP_SENSOR_ID    "649e26ae743f9120xxxxxxxx"
#define DHT_PIN           14
#define Lampada_ID        "6489b6fd929949c1xxxxxxxx"
#define Lampada_Pin       5
#define BAUD_RATE         9600
#define EVENT_WAIT_TIME   6000

DHT dht;

bool deviceIsOn;
float temperature;
float humidity;
float lastTemperature;
float lastHumidity;
unsigned long lastEvent = (-EVENT_WAIT_TIME);

void setupWiFi();
void setupSinricPro();
bool LampadaState(const String &deviceId, bool &state);
bool TempState(const String &deviceId, bool &state);

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.printf("\r\n\r\n");
  dht.setup(DHT_PIN);

  setupWiFi();
  setupSinricPro();
  pinMode(Lampada_Pin, OUTPUT);
}

void loop() {
  SinricPro.handle();
  handleTempSensor();
}

bool LampadaState(const String &deviceId, bool &state) {
  Serial.printf("A lampada foi %s\r\n", state ? "ligada" : "desligada");
  digitalWrite(Lampada_Pin, state);
  return true; 
}

bool TempState(const String &deviceId, bool &state) {
  Serial.printf("Temperatura Sensor esta %s (Via SinricPro) \r\n", state ? "ligada" : "desligada");
  deviceIsOn = state;
  return true;
}

void handleTempSensor(){
  if (deviceIsOn == false)
    return;

  unsigned long actualMillis = millis();

  if (actualMillis - lastEvent < EVENT_WAIT_TIME)
    return;

  temperature = dht.getTemperature();

  humidity = dht.getHumidity();

  if (isnan(temperature) || isnan(humidity)){
    Serial.printf("DHT falhou na leitura!\r\n");
    return;
  }

  if(temperature == lastTemperature || humidity == lastHumidity)
    return;

  SinricProTemperaturesensor &mySensor = SinricPro[TEMP_SENSOR_ID];
  bool success = mySensor.sendTemperatureEvent(temperature, humidity);

  if(success) {
    Serial.printf("Temperatura: %2.1f Celsius\tUmidade: %2.1f%%\r\n", temperature, humidity);
  }else{
    Serial.printf("Algo deu errado, nao foi possivel enviar o evento ao servidor...\r\n");
  }

  lastTemperature = temperature;
  lastHumidity = humidity;
  lastEvent = actualMillis;
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
  SinricProTemperaturesensor &mySensor = SinricPro[TEMP_SENSOR_ID];
  mySensor.onPowerState(TempState);

  SinricProSwitch &mySwitch1 = SinricPro[Lampada_ID];
  mySwitch1.onPowerState(LampadaState);

  SinricPro.onConnected([]() { Serial.printf("Conectado a nuvem SinricPro\r\n"); });
  SinricPro.onDisconnected([]() { Serial.printf("Desconectado a nuvem SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}
