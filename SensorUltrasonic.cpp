#include "SensorUltrasonic.h"
#include <Arduino.h>

SensorUltrasonic::SensorUltrasonic(int triggerPin, int echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float SensorUltrasonic::getDistanceCm() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distance = (duration * 0.0343) / 2; 
    delay(100);
    return distance;
}
