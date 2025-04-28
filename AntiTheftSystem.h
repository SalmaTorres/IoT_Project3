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
    bool activeAlarm;

  public:
    AntiTheftSystem(SensorUltrasonic* sensor, Buzzer* buzzer, PubSubClient* mqttClient);
    void update();
    void processMessage(char* topic, byte* payload, unsigned int length);
};

#endif
