#include <Arduino.h>

#define PIN_R1 9
#define PIN_R1_SET_LOW (PORTB &= ~(1 << PB1))
#define PIN_R1_SET_HIGH (PORTB |= (1 << PB1))

#define PIN_R2 7
#define PIN_R2_SET_LOW (PORTD &= ~(1 << PD7))
#define PIN_R2_SET_HIGH (PORTD |= (1 << PD7))

#define PIN_G1 8
#define PIN_G1_SET_LOW (PORTB &= ~(1 << PB0))
#define PIN_G1_SET_HIGH (PORTB |= (1 << PB0))

#define PIN_G2 6
#define PIN_G2_SET_LOW (PORTD &= ~(1 << PD6))
#define PIN_G2_SET_HIGH (PORTD |= (1 << PD6))

#define PIN_B1 15
#define PIN_B1_SET_LOW (PORTC &= ~(1 << PC1))
#define PIN_B1_SET_HIGH (PORTC |= (1 << PC1))

#define PIN_B2 16
#define PIN_B2_SET_LOW (PORTC &= ~(1 << PC2))
#define PIN_B2_SET_HIGH (PORTC |= (1 << PC2))

#define PIN_A 5
#define PIN_B 17
#define PIN_C 4
#define PIN_D 18

#define PIN_CLK 3
#define PIN_CLK_SET_LOW (PORTD &= ~(1 << PD3))
#define PIN_CLK_SET_HIGH (PORTD |= (1 << PD3))

#define PIN_LAT 19
#define PIN_OE_NOT 2

#define DATA_ROWS 32 // Y
#define DATA_COLUMNS 64 // X
#define DATA_COLUMN_BYTES 8 // DATA_COLUMNS/8
#define DATA_COLORS 3

#define DATA_RED_COLOR_POS 0
#define DATA_GREEN_COLOR_POS 1
#define DATA_BLUE_COLOR_POS 2

uint8_t data[DATA_COLORS][DATA_ROWS][DATA_COLUMN_BYTES] = {};

/**
 * Push data from "data"-Array to the registers of the RGB LED Matrix
 */
void puschData(uint8_t yPos1, uint8_t yPos2) {
    for (uint8_t xBytePos=0; xBytePos<DATA_COLUMN_BYTES; xBytePos++) {
        for (uint8_t xBitMask=128; xBitMask>=1; xBitMask >>= 1) {

            if (data[DATA_RED_COLOR_POS][yPos1][xBytePos] & xBitMask) {
                PIN_R1_SET_HIGH;
            } else {
                PIN_R1_SET_LOW;
            }

            if (data[DATA_RED_COLOR_POS][yPos2][xBytePos] & xBitMask) {
                PIN_R2_SET_HIGH;
            } else {
                PIN_R2_SET_LOW;
            }

            if (data[DATA_GREEN_COLOR_POS][yPos1][xBytePos] & xBitMask) {
                PIN_G1_SET_HIGH;
            } else {
                PIN_G1_SET_LOW;
            }

            if (data[DATA_GREEN_COLOR_POS][yPos2][xBytePos] & xBitMask) {
                PIN_G2_SET_HIGH;
            } else {
                PIN_G2_SET_LOW;
            }

            if (data[DATA_BLUE_COLOR_POS][yPos1][xBytePos] & xBitMask) {
                PIN_B1_SET_HIGH;
            } else {
                PIN_B1_SET_LOW;
            }

            if (data[DATA_BLUE_COLOR_POS][yPos2][xBytePos] & xBitMask) {
                PIN_B2_SET_HIGH;
            } else {
                PIN_B2_SET_LOW;
            }

            PIN_CLK_SET_HIGH;
            PIN_CLK_SET_LOW;
        }
    }
}

/**
 * Draw/Show a single frame on the RGB LED Matrix
 */
void drawFrame() {
    uint8_t dataRowsHalf = DATA_ROWS / 2;
    for (uint8_t yPos1=0; yPos1<dataRowsHalf; yPos1++) {
        puschData(yPos1, yPos1 + dataRowsHalf);

        digitalWrite(PIN_OE_NOT, HIGH);

        digitalWrite(PIN_LAT, HIGH);
        digitalWrite(PIN_LAT, LOW);

        digitalWrite(PIN_A, yPos1 & 0b00000001);
        digitalWrite(PIN_B, yPos1 & 0b00000010);
        digitalWrite(PIN_C, yPos1 & 0b00000100);
        digitalWrite(PIN_D, yPos1 & 0b00001000);

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
    data[DATA_RED_COLOR_POS][0][0] = 0b00011001;
    data[DATA_GREEN_COLOR_POS][16][0] = 0b10000000;
}

void loop() {
    drawFrame();
}
