#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "matrix.h"

// Peripheral pins
#define LED_R 13  // Red LED pin
#define BTN_A 5   // Increment button
#define BTN_B 6   // Decrement button

static volatile uint counter = 0;  // Current number displayed on LED matrix
static volatile uint32_t last_press_time = 0;  // Last button press time (for debounce)

// Function prototypes
void initialize_led();
void initialize_buttons();
static void button_interrupt_handler(uint gpio, uint32_t events);

int main() {
    stdio_init_all();

    // Initialize PIO and LED matrix
    PIO pio = pio0;
    uint sm = configure_matrix(pio);
    initialize_numbers();

    // Initialize peripherals
    initialize_led();
    initialize_buttons();

    // Set up button interrupts
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &button_interrupt_handler);
    gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &button_interrupt_handler);

    while (true) {
        display_number(counter, pio, sm); // Update LED matrix

        // Blink red LED 5 times per second
        for (int i = 0; i < 5; i++) {
            gpio_put(LED_R, 1);
            sleep_ms(100);
            gpio_put(LED_R, 0);
            sleep_ms(100);
        }
    }
}

// Initialize LED
void initialize_led() {
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
}

// Initialize buttons
void initialize_buttons() {
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);
}

// Button interrupt handler with debounce
static void button_interrupt_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (current_time - last_press_time > 200000) { // 200ms debounce
        last_press_time = current_time;

        if (gpio == BTN_A) {
            counter = (counter >= 9) ? 9 : counter + 1;  // Increment (max 9)
        } else if (gpio == BTN_B) {
            counter = (counter > 0) ? counter - 1 : 0;  // Decrement (min 0)
        }

        printf("Counter: %d\n", counter);
    }
}
