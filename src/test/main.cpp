#include <Arduino.h>

#define TRIG_PIN 20
#define ECHO_PIN 21

void setup() {
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

float readDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    if (duration == 0) return -1;
    float distance = duration * 0.0343 / 2.0;
    return distance;
}

void loop() {
    float d = readDistance();
    if (d < 0) Serial.println("Timeout");
    else Serial.printf("Distance: %.1f cm\n", d);
    delay(500);
}

