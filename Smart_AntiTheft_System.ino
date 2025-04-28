#include <WiFi.h>
#include <PubSubClient.h> 
#include "SensorUltrasonic.h"
#include "Buzzer.h"
#include "AntiTheftSystem.h"

// Configuración Wi-Fi
const char* WIFI_SSID = "holi holi holi";
const char* WIFI_PASS = "acasapete";

// Configuración MQTT
const char* MQTT_BROKER = "broker.emqx.io";
const int MQTT_PORT = 1883;
const char* CLIENT_ID = "a886b9804fca437c9d93201bab7e2d88";

// Crear los objetos globales
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);  // Aquí pasamos WiFiClient al PubSubClient

SensorUltrasonic sensor(12, 14);
Buzzer buzzer(25);
AntiTheftSystem AntiTheftSystem(&sensor, &buzzer, &mqttClient);  // Asegúrate de que AntiTheftSystem acepte PubSubClient*

void setup() {
  Serial.begin(115200);

  // Conectar al WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado al WiFi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Configurar conexión MQTT
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(callback);  // Función que maneja mensajes recibidos

  // Intentar conectar
  connectToMqtt();
}

void loop() {
  if (!mqttClient.connected()) {
    connectToMqtt();
  }
  mqttClient.loop();

  AntiTheftSystem.actualizar();  // Lógica de sensor y buzzer
}

void callback(char* topic, byte* payload, unsigned int length) {
  AntiTheftSystem.procesarMensaje(topic, payload, length);
}

void connectToMqtt() {
  Serial.print("Intentando conexión MQTT...");
  while (!mqttClient.connected()) {
    if (mqttClient.connect(CLIENT_ID)) {
      Serial.println("Conectado al broker MQTT.");
      mqttClient.subscribe("antirrobo/candado");
    } else {
      Serial.print("Fallo conexión. Estado: ");
      Serial.print(mqttClient.state());
      Serial.println(". Intentando de nuevo en 5 segundos...");
      delay(5000);
    }
  }
}
