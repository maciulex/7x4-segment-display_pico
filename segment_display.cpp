#ifndef SEGMENT_DISPLAY_F
#define SEGMENT_DISPLAY_F
#include <stdio.h>

//printf(BYTE_TO_BINARY_PATTERN,  BYTE_TO_BINARY(<<>>));
#ifndef INT_TO_BIN
#define INT_TO_BIN
    #define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
    #define BYTE_TO_BINARY(byte)  \
    (byte & 0x80 ? '1' : '0'), \
    (byte & 0x40 ? '1' : '0'), \
    (byte & 0x20 ? '1' : '0'), \
    (byte & 0x10 ? '1' : '0'), \
    (byte & 0x08 ? '1' : '0'), \
    (byte & 0x04 ? '1' : '0'), \
    (byte & 0x02 ? '1' : '0'), \
    (byte & 0x01 ? '1' : '0') 
#endif

namespace SEGMENT_DISPLAY {
    #define NUMBER_OF_SECTORS 4

    //A,B,C,D,E,F,G,DP
    uint8_t DATA_PINS[] {
        1,5,9,7,6,2,10,8
    };

    uint8_t NUMBER_SELECT_PINS[NUMBER_OF_SECTORS] {
        0,3,4,11
    };

    bool DOTS_STATUS[NUMBER_OF_SECTORS] {
        false,false,false,false
    };

    uint8_t NUMBERS[NUMBER_OF_SECTORS] {
        0,0,0,0
    };

    void initPins() {
        for (int i = 0; i < 8; i++) {
            gpio_init(DATA_PINS[i]);
            gpio_set_dir(DATA_PINS[i], GPIO_OUT);
            gpio_put(DATA_PINS[i], 0);
        }
        for (int i = 0; i < NUMBER_OF_SECTORS; i++) {
            gpio_init(NUMBER_SELECT_PINS[i]);
            gpio_set_dir(NUMBER_SELECT_PINS[i], GPIO_OUT);
            gpio_put(NUMBER_SELECT_PINS[i], 0);
        }
    }

    void put_digits(uint16_t digits) {
        printf("Digit: %i\n",digits);
        uint lastNumber = digits % 10;
        for (int i = 0; i < NUMBER_OF_SECTORS; i++) {
            NUMBERS[NUMBER_OF_SECTORS - 1 - i] = lastNumber;
            digits /= 10;
            printf("\tD: %i",lastNumber);
            lastNumber = digits % ((i+1) * 10);
        };
        printf("\n\n");

    }

    void displaySector(uint8_t sector) {
        for (int i = 0; i < NUMBER_OF_SECTORS; i++) gpio_put(NUMBER_SELECT_PINS[i], 0);
        for (int i = 0; i < 8; i++) gpio_put(DATA_PINS[i], 1);

        gpio_put(NUMBER_SELECT_PINS[sector], 1);
        
        if (DOTS_STATUS[sector]) gpio_put(DATA_PINS[7], 0);

        switch (NUMBERS[sector]) {
            case 0:
                gpio_put(DATA_PINS[0], 0);
                gpio_put(DATA_PINS[1], 0);
                gpio_put(DATA_PINS[2], 0);
                gpio_put(DATA_PINS[3], 0);
                gpio_put(DATA_PINS[4], 0);
                gpio_put(DATA_PINS[5], 0);
            break;
            case 1:
                gpio_put(DATA_PINS[1], 0);
                gpio_put(DATA_PINS[2], 0);
            break;
            case 2:
                gpio_put(DATA_PINS[0], 0);
                gpio_put(DATA_PINS[1], 0);
                gpio_put(DATA_PINS[3], 0);
                gpio_put(DATA_PINS[4], 0);
                gpio_put(DATA_PINS[6], 0);
            break;
            case 3:
                gpio_put(DATA_PINS[0], 0);
                gpio_put(DATA_PINS[1], 0);
                gpio_put(DATA_PINS[2], 0);
                gpio_put(DATA_PINS[3], 0);
                gpio_put(DATA_PINS[6], 0);
            break;
            case 4:
                gpio_put(DATA_PINS[1], 0);
                gpio_put(DATA_PINS[2], 0);
                gpio_put(DATA_PINS[6], 0);
                gpio_put(DATA_PINS[5], 0);
            break;
            case 5:
                gpio_put(DATA_PINS[0], 0);
                gpio_put(DATA_PINS[5], 0);
                gpio_put(DATA_PINS[6], 0);
                gpio_put(DATA_PINS[2], 0);
                gpio_put(DATA_PINS[3], 0);
            break;
            case 6:
                gpio_put(DATA_PINS[0], 0);
                gpio_put(DATA_PINS[2], 0);
                gpio_put(DATA_PINS[3], 0);
                gpio_put(DATA_PINS[4], 0);
                gpio_put(DATA_PINS[5], 0);
                gpio_put(DATA_PINS[6], 0);
            break;
            case 7:
                gpio_put(DATA_PINS[0], 0);
                gpio_put(DATA_PINS[1], 0);
                gpio_put(DATA_PINS[2], 0);
                gpio_put(DATA_PINS[5], 0);
            break;
            case 8:
                gpio_put(DATA_PINS[0], 0);
                gpio_put(DATA_PINS[1], 0);
                gpio_put(DATA_PINS[2], 0);
                gpio_put(DATA_PINS[3], 0);
                gpio_put(DATA_PINS[4], 0);
                gpio_put(DATA_PINS[5], 0);
                gpio_put(DATA_PINS[6], 0);
            break;
            case 9:
                gpio_put(DATA_PINS[0], 0);
                gpio_put(DATA_PINS[1], 0);
                gpio_put(DATA_PINS[2], 0);
                gpio_put(DATA_PINS[3], 0);
                gpio_put(DATA_PINS[5], 0);
                gpio_put(DATA_PINS[6], 0);
            break;
        }
            
    }

    void display_loop() {
        while (true) {
            for (int i = 0; i < NUMBER_OF_SECTORS; i++) {
                displaySector(i);
                sleep_ms(2);
            }
        }
    }

    void init() {
        initPins();
    }
} 

#endif