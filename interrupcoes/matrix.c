#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "matrix.h"

// Include PIO program for LED matrix
#include "pio_matrix.pio.h"

#define LED_PIN 7

// Stores numbers 0-9 in LED matrix format
LedMatrixConfig *Numbers[10];

// Number patterns for LED matrix (GREEN color)
LedMatrixConfig number_0 = {
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}
};

LedMatrixConfig number_1 = {
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}
};

LedMatrixConfig number_2 = {
        {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
        {{0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
        {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    };

LedMatrixConfig number_3 = {
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}
};

LedMatrixConfig number_4 = {
    {{0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}
};

LedMatrixConfig number_5 = {
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}
};

LedMatrixConfig number_6 = {
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}
};

LedMatrixConfig number_7 = {
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}
};

LedMatrixConfig number_8 = {
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}
};

LedMatrixConfig number_9 = {
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}, 
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.1, 0.1, 0.0}, {0.0, 0.0, 0.0}}
};

void initialize_numbers() {
    Numbers[0] = &number_0;
    Numbers[1] = &number_1;
    Numbers[2] = &number_2;
    Numbers[3] = &number_3;
    Numbers[4] = &number_4;
    Numbers[5] = &number_5;
    Numbers[6] = &number_6;
    Numbers[7] = &number_7;
    Numbers[8] = &number_8;
    Numbers[9] = &number_9;
}

// Convert RGB values (0.0 - 1.0) to WS2812 32-bit format
uint32_t generate_color_binary(double red, double green, double blue) {
    unsigned char RED = red * 255.0;
    unsigned char GREEN = green * 255.0;
    unsigned char BLUE = blue * 255.0;
    return (GREEN << 24) | (RED << 16) | (BLUE << 8);
}

// Configure LED matrix using PIO
uint configure_matrix(PIO pio) {
    bool ok = set_sys_clock_khz(128000, false);
    stdio_init_all();

    if (ok) printf("Clock set to %ld\n", clock_get_hz(clk_sys));

    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, LED_PIN);

    return sm;
}

// Send LED pattern to the matrix
void display_pattern(LedMatrixConfig pattern, PIO pio, uint sm) {
    for (int row = 4; row >= 0; row--) {
        if (row % 2) {
            for (int col = 0; col < 5; col++) {
            uint32_t color = generate_color_binary(
                pattern[row][col].red,
                pattern[row][col].green,
                pattern[row][col].blue);  
            pio_sm_put_blocking(pio, sm, color);
        }   
        } else {
            for (int col = 4; col >= 0; col--) {
            uint32_t color = generate_color_binary(
                pattern[row][col].red,
                pattern[row][col].green,
                pattern[row][col].blue);  
            pio_sm_put_blocking(pio, sm, color);
            }

         }
   }
}

// Display a number (0-9) on the matrix
void display_number(uint number, PIO pio, uint sm) {
    display_pattern(*Numbers[number], pio, sm);
}

// Clear the LED matrix
void clear_matrix(PIO pio, uint sm) {
    LedMatrixConfig reset = {
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, 
    };
    display_pattern(reset, pio, sm);
}
