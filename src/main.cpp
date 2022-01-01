#include <Arduino.h>

#define PIN_R1 9
#define PIN_R2 7
#define PIN_G1 8
#define PIN_G2 6
#define PIN_B1 15
#define PIN_B2 16

#define PIN_A 5
#define PIN_B 17
#define PIN_C 4
#define PIN_D 18

#define PIN_CLK 3
#define PIN_LAT 19
#define PIN_OE_NOT 2

void setup() {
  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_R2, OUTPUT);
  pinMode(PIN_G1, OUTPUT);
  pinMode(PIN_G2, OUTPUT);
  pinMode(PIN_B1, OUTPUT);
  pinMode(PIN_B2, OUTPUT);

  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);

  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_LAT, OUTPUT);
  pinMode(PIN_OE_NOT, OUTPUT);

  // Test Output
  digitalWrite(PIN_OE_NOT, HIGH);

  digitalWrite(PIN_R1, HIGH);
  digitalWrite(PIN_G2, HIGH);

  digitalWrite(PIN_CLK, HIGH);
  digitalWrite(PIN_CLK, LOW);
  digitalWrite(PIN_CLK, HIGH);
  digitalWrite(PIN_CLK, LOW);

  digitalWrite(PIN_R1, LOW);
  digitalWrite(PIN_G2, LOW);

  digitalWrite(PIN_LAT, HIGH);
  digitalWrite(PIN_LAT, LOW);

  digitalWrite(PIN_OE_NOT, LOW);
}

void loop() {
  uint8_t delayMs = 60;

  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, LOW);
  delay(delayMs);

  digitalWrite(PIN_A, HIGH);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, LOW);
  delay(delayMs);
}