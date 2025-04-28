#ifndef ANTITHEFTSYSTEM_H
#define ANTITHEFTSYSTEM_H

#include "SensorUltrasonic.h"
#include "Buzzer.h"
#include <PubSubClient.h>

class AntiTheftSystem {
  private:
    SensorUltrasonic* sensor;
    Buzzer* buzzer;
    PubSubClient* mqttClient;
    bool alarmaActiva;

  public:
    AntiTheftSystem(SensorUltrasonic* sensor, Buzzer* buzzer, PubSubClient* mqttClient);
    void actualizar();
    void procesarMensaje(char* topic, byte* payload, unsigned int length);
};

#endif
