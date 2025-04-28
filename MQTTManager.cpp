#include "MQTTManager.h"
#include <Arduino.h>

MQTTManager::MQTTManager(const char* server, int port, const char* clientId) {
  this->server = server;
  this->port = port;
  this->clientId = clientId;
  this->client = PubSubClient(wiFiClient);
  this->client.setServer(server, port);
}

void MQTTManager::connect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds");
      delay(5000);
    }
  }
}

void MQTTManager::subscribe(const char* topic) {
  client.subscribe(topic);
}

void MQTTManager::publish(const char* topic, const char* message) {
  client.publish(topic, message);
}

void MQTTManager::loop() {
  client.loop();
}

void MQTTManager::setCallback(void (*callback)(char*, byte*, unsigned int)) {
  client.setCallback(callback);
}
