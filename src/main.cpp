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

#define DATA_ROWS 32 // Y
#define DATA_COLUMNS 64 // X
#define DATA_COLUMN_BYTES 8 // DATA_COLUMNS/8


uint8_t data[DATA_ROWS][DATA_COLUMN_BYTES] = {};

/**
 * Push data from "data"-Array to the registers of the RGB LED Matrix
 */
void puschData(uint8_t yPos) {
    for (uint8_t xBytePos=0; xBytePos<DATA_COLUMN_BYTES; xBytePos++) {
        for (uint8_t xBitPos=128; xBitPos>=1; xBitPos >>= 1) {
            digitalWrite(PIN_R1, data[yPos][xBytePos] & xBitPos);

            digitalWrite(PIN_CLK, HIGH);
            digitalWrite(PIN_CLK, LOW);
        }
    }
}

/**
 * Draw/Show a single frame on the RGB LED Matrix
 */
void drawFrame() {
    for (uint8_t yPos=0; yPos<DATA_ROWS; yPos++) {
        puschData(yPos);

        digitalWrite(PIN_OE_NOT, HIGH);

        digitalWrite(PIN_LAT, HIGH);
        digitalWrite(PIN_LAT, LOW);

        digitalWrite(PIN_A, yPos & 0b00000001);
        digitalWrite(PIN_B, yPos & 0b00000010);
        digitalWrite(PIN_C, yPos & 0b00000100);
        digitalWrite(PIN_D, yPos & 0b00001000);

        digitalWrite(PIN_OE_NOT, LOW);
    }
}

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
    data[0][0] = 0b00011001;
}

void loop() {
    drawFrame();
}
