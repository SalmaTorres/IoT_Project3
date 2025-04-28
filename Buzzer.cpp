#include "Buzzer.h"
#include <Arduino.h>

Buzzer::Buzzer(int buzzerPin) {
  this->buzzerPin = buzzerPin;
  pinMode(buzzerPin, OUTPUT); 
}

void Buzzer::alarmOn() {
  digitalWrite(buzzerPin, HIGH); 
}

void Buzzer::alarmOff() {
  digitalWrite(buzzerPin, LOW);
}
