#ifndef MATRIX_H
#define MATRIX_H

#include "hardware/pio.h"

// RGB LED struct
typedef struct {
    double red;
    double green;
    double blue;
} LedConfig;

// 5x5 LED matrix type
typedef LedConfig LedMatrixConfig[5][5];

// Function prototypes
uint32_t generate_color_binary(double red, double green, double blue);
uint configure_matrix(PIO pio);
void display_pattern(LedMatrixConfig pattern, PIO pio, uint sm);
void display_number(uint number, PIO pio, uint sm);
void initialize_numbers();
void clear_matrix(PIO pio, uint sm);

#endif