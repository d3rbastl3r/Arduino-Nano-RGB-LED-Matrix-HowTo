#include <Arduino.h>

#define PIN_R1_MODE_OUT (DDRB |= (1 << DDB1))
#define PIN_R1_SET_LOW (PORTB &= ~(1 << PB1))
#define PIN_R1_SET_HIGH (PORTB |= (1 << PB1))

#define PIN_R2_MODE_OUT (DDRD |= (1 << DDD7))
#define PIN_R2_SET_LOW (PORTD &= ~(1 << PD7))
#define PIN_R2_SET_HIGH (PORTD |= (1 << PD7))

#define PIN_G1_MODE_OUT (DDRB |= (1 << DDB0))
#define PIN_G1_SET_LOW (PORTB &= ~(1 << PB0))
#define PIN_G1_SET_HIGH (PORTB |= (1 << PB0))

#define PIN_G2_MODE_OUT (DDRD |= (1 << DDD6))
#define PIN_G2_SET_LOW (PORTD &= ~(1 << PD6))
#define PIN_G2_SET_HIGH (PORTD |= (1 << PD6))

#define PIN_B1_MODE_OUT (DDRC |= (1 << DDC1))
#define PIN_B1_SET_LOW (PORTC &= ~(1 << PC1))
#define PIN_B1_SET_HIGH (PORTC |= (1 << PC1))

#define PIN_B2_MODE_OUT (DDRC |= (1 << DDC2))
#define PIN_B2_SET_LOW (PORTC &= ~(1 << PC2))
#define PIN_B2_SET_HIGH (PORTC |= (1 << PC2))

#define PIN_A_MODE_OUT (DDRD |= (1 << DDD5))
#define PIN_A_SET_LOW (PORTD &= ~(1 << PD5))
#define PIN_A_SET_HIGH (PORTD |= (1 << PD5))

#define PIN_B_MODE_OUT (DDRC |= (1 << DDC3))
#define PIN_B_SET_LOW (PORTC &= ~(1 << PC3))
#define PIN_B_SET_HIGH (PORTC |= (1 << PC3))

#define PIN_C_MODE_OUT (DDRD |= (1 << DDD4))
#define PIN_C_SET_LOW (PORTD &= ~(1 << PD4))
#define PIN_C_SET_HIGH (PORTD |= (1 << PD4))

#define PIN_D_MODE_OUT (DDRC |= (1 << DDC4))
#define PIN_D_SET_LOW (PORTC &= ~(1 << PC4))
#define PIN_D_SET_HIGH (PORTC |= (1 << PC4))

#define PIN_CLK_MODE_OUT (DDRD |= (1 << DDD3))
#define PIN_CLK_SET_LOW (PORTD &= ~(1 << PD3))
#define PIN_CLK_SET_HIGH (PORTD |= (1 << PD3))

#define PIN_LAT_MODE_OUT (DDRC |= (1 << DDC5))
#define PIN_LAT_SET_LOW (PORTC &= ~(1 << PC5))
#define PIN_LAT_SET_HIGH (PORTC |= (1 << PC5))

#define PIN_nOE_MODE_OUT (DDRD |= (1 << DDD2))
#define PIN_nOE_SET_LOW (PORTD &= ~(1 << PD2))
#define PIN_nOE_SET_HIGH (PORTD |= (1 << PD2))

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

        PIN_nOE_SET_HIGH;

        PIN_LAT_SET_HIGH;
        PIN_LAT_SET_LOW;

        if (yPos1 & 0b00000001) {
            PIN_A_SET_HIGH;
        } else {
            PIN_A_SET_LOW;
        }

        if (yPos1 & 0b00000010) {
            PIN_B_SET_HIGH;
        } else {
            PIN_B_SET_LOW;
        }

        if (yPos1 & 0b00000100) {
            PIN_C_SET_HIGH;
        } else {
            PIN_C_SET_LOW;
        }

        if (yPos1 & 0b00001000) {
            PIN_D_SET_HIGH;
        } else {
            PIN_D_SET_LOW;
        }

        PIN_nOE_SET_LOW;
    }
}

void setup() {
    PIN_R1_MODE_OUT;
    PIN_R2_MODE_OUT;
    PIN_G1_MODE_OUT;
    PIN_G2_MODE_OUT;
    PIN_B1_MODE_OUT;
    PIN_B2_MODE_OUT;

    PIN_A_MODE_OUT;
    PIN_B_MODE_OUT;
    PIN_C_MODE_OUT;
    PIN_D_MODE_OUT;

    PIN_CLK_MODE_OUT;
    PIN_LAT_MODE_OUT;
    PIN_nOE_MODE_OUT;

    // Test Output
    data[DATA_RED_COLOR_POS][0][0] = 0b00011001;
    data[DATA_GREEN_COLOR_POS][16][0] = 0b10000000;
}

void loop() {
    drawFrame();
}
