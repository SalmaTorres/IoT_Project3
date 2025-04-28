#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTManager {
  private:
    const char* server;
    int port;
    const char* clientId;
    WiFiClient wiFiClient;
    PubSubClient client;

  public:
    MQTTManager(const char* server, int port, const char* clientId);
    void connect();
    void subscribe(const char* topic);
    void publish(const char* topic, const char* message);
    void loop();
    void setCallback(void (*callback)(char*, byte*, unsigned int)); 
};

#endif
