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
    unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    if (duration == 0) return -1.0f;
    float distance = duration * 0.0343f / 2.0f;
    return distance;
}
void safePrint(const char *s) {
    size_t need = strlen(s) + 2;
    unsigned long start = millis();
    while (Serial.availableForWrite() < (int)need) {
        if (millis() - start > 50) break;
        yield();
    }
    Serial.println(s);
}
void loop() {
    float d = readDistance();
    char buf[32];
    if (d < 0) snprintf(buf, sizeof(buf), "Timeout");
    else snprintf(buf, sizeof(buf), "Distance: %.1f cm", d);
    safePrint(buf);
    delay(500);
}

