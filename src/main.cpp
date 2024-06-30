#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Hello from S2 Mini");
  delay(500);
}
