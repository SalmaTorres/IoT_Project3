#include "AntiTheftSystem.h"
#include <Arduino.h>  // Para usar Serial

AntiTheftSystem::AntiTheftSystem(SensorUltrasonic* sensor, Buzzer* buzzer, PubSubClient* mqttClient) {
  this->sensor = sensor;
  this->buzzer = buzzer;
  this->mqttClient = mqttClient;
  this->alarmaActiva = false;  // Por defecto DESACTIVADA
}

void AntiTheftSystem::actualizar() {
  float distancia = sensor->getDistanceCm();

  if (distancia <= 0) {
    Serial.println("Lectura inválida (distancia 0), ignorando...");
    return;
  }

  Serial.print("Distancia medida: ");
  Serial.print(distancia);
  Serial.println(" cm");
    // --- NUEVO: Publicar distancia al broker MQTT
    char mensaje[10];
    dtostrf(distancia, 6, 2, mensaje); // convierte float a char array
    mqttClient->publish("antirrobo/distancia", mensaje);
}

void AntiTheftSystem::procesarMensaje(char* topic, byte* payload, unsigned int length) {
  String mensaje;
  for (unsigned int i = 0; i < length; i++) {
    mensaje += (char)payload[i];
  }

  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(mensaje);

  if (String(topic) == "antirrobo/candado") {
    if (mensaje == "ACTIVAR") {
      alarmaActiva = true;
      buzzer->alarmOn();   // Encender buzzer directamente al ACTIVAR
      Serial.println("Sistema ACTIVADO -> Buzzer encendido.");
    } else if (mensaje == "DESACTIVAR") {
      alarmaActiva = false;
      buzzer->alarmOff();  // Apagar buzzer directamente al DESACTIVAR
      Serial.println("Sistema DESACTIVADO -> Buzzer apagado.");
    }
  }
}
