#ifndef SENSOR_ULTRASONIC_H
#define SENSOR_ULTRASONIC_H

class SensorUltrasonic {
public:
    SensorUltrasonic(int triggerPin, int echoPin);
    float getDistanceCm();

private:
    int triggerPin;
    int echoPin;
};

#endif