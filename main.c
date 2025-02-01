#include <stdio.h>
#include "pico/stdlib.h"

// GPIO do LED RGB
#define RGB_RED 13
#define RGB_GREEN 11
#define RGB_BLUE 12

// Definindo a máscara para ativar a GPIO
#define OUTPUT_MASK ((1 << RGB_BLUE) | (1 << RGB_GREEN) | (1 << RGB_RED))

uint16_t atraso = 3000; // Atraso em ms

int main(){
    stdio_init_all();

    // Inicializando a máscara da GPIO utilizada
    gpio_init_mask(OUTPUT_MASK);
    // Definindo como saída
    gpio_set_dir_out_masked(OUTPUT_MASK);

    while (true) {
        printf("1 segundo se passou...\n");
        sleep_ms(1000);
    }
}
