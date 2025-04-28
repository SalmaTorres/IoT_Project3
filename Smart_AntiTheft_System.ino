#include <WiFi.h>
#include <PubSubClient.h> 
#include "SensorUltrasonic.h"
#include "Buzzer.h"
#include "AntiTheftSystem.h"

const char* WIFI_SSID = "holi holi holi";
const char* WIFI_PASS = "acasapete";

const char* MQTT_BROKER = "broker.emqx.io";
const int MQTT_PORT = 1883;
const char* CLIENT_ID = "a886b9804fca437c9d93201bab7e2d88";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);  

SensorUltrasonic sensor(12, 14);
Buzzer buzzer(25);
AntiTheftSystem AntiTheftSystem(&sensor, &buzzer, &mqttClient); 

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado al WiFi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(callback);  

  connectToMqtt();
}

void loop() {
  if (!mqttClient.connected()) {
    connectToMqtt();
  }
  mqttClient.loop();

  AntiTheftSystem.update();  
}

void callback(char* topic, byte* payload, unsigned int length) {
  AntiTheftSystem.processMessage(topic, payload, length);
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
      Serial.println(". Intentando de nuevo en 3 segundos...");
      delay(3000);
    }
  }
}
