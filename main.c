#include <stdio.h>
#include "pico/stdlib.h"

// GPIO do LED RGB
#define RGB_GREEN 11
#define RGB_BLUE 12
#define RGB_RED 13

// Definindo a máscara para ativar a GPIO
#define OUTPUT_MASK ((1 << RGB_BLUE) | (1 << RGB_GREEN) | (1 << RGB_RED))

uint16_t atraso = 3000; // Atraso em ms
int contador = 1; // Contador para definir qual led vai ser ativado

// Função que é chamada na interrupção do temproizador
bool repeating_timer_callback(struct repeating_timer *t){
    // Condicional para o contador voltar ao valor inicial quando estourar
    if(contador>3){
        contador = 1;
    }

    switch(contador){
        case 1:
            gpio_put_masked(OUTPUT_MASK, 0); // Desativando todos os leds
            gpio_put(RGB_GREEN, 1); // Ativando o primeiro led do semáforo (Vermelho)
            break;
        case 2:
            gpio_put_masked(OUTPUT_MASK, 0); // Desativando todos os leds
            gpio_put(RGB_BLUE, 1);  // Ativando o segundo led do semáforo (Amarelo)
            break;
        case 3:
            gpio_put_masked(OUTPUT_MASK, 0); // Desativando todos os leds
            gpio_put(RGB_RED, 1);  // Ativando o terceiro led do semáforo (Verde)          
            break;
    }

    contador++; // Incrementa o contador
    return true; // Retorna true para repetir a interrupção
}

int main(){
    stdio_init_all();

    // Inicializando a máscara da GPIO utilizada
    gpio_init_mask(OUTPUT_MASK);
    // Definindo como saída
    gpio_set_dir_out_masked(OUTPUT_MASK);

    // Configurando um temporizador de repetição
    struct repeating_timer timer;
    // Configurnado o repeating timer
    add_repeating_timer_ms(atraso, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("1 segundo se passou...\n");
        sleep_ms(1000);
    }
}
