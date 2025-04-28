#include "AntiTheftSystem.h"
#include <Arduino.h>  

AntiTheftSystem::AntiTheftSystem(SensorUltrasonic* sensor, Buzzer* buzzer, PubSubClient* mqttClient) {
  this->sensor = sensor;
  this->buzzer = buzzer;
  this->mqttClient = mqttClient;
  this->activeAlarm = false;  
}

void AntiTheftSystem::update() {
  float distance = sensor->getDistanceCm();

  if (distance <= 0) {
    Serial.println("Lectura inválida (distance 0), ignorando...");
    return;
  }

  Serial.print("distance medida: ");
  Serial.print(distance);
  Serial.println(" cm");
    char message[10];
    dtostrf(distance, 6, 2, message); 
    mqttClient->publish("antirrobo/distance", message);
}

void AntiTheftSystem::processMessage(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("message recibido [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  if (String(topic) == "antirrobo/candado") {
    if (message == "ACTIVAR") {
      activeAlarm = true;
      buzzer->alarmOn();   // Encender buzzer directamente al ACTIVAR
      Serial.println("Sistema ACTIVADO -> Buzzer encendido.");
    } else if (message == "DESACTIVAR") {
      activeAlarm = false;
      buzzer->alarmOff();  // Apagar buzzer directamente al DESACTIVAR
      Serial.println("Sistema DESACTIVADO -> Buzzer apagado.");
    }
  }
}
