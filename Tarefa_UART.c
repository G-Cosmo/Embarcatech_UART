#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h" 

#define RGB_RED 13
#define RGB_BLUE 12
#define RGB_GREEN 11
const uint buzzer_pin = 21; // GPIO do buzzer



//função que inicializa os pinos de um led RGB
void pico_rgb_init(const uint *rgb_pin)
{   
    
    for(int i = 0; i < 3; i++)
    {
        //_rgb_1[i] = rgb_pin[i];
        gpio_init(rgb_pin[i]);      //incializa os pinos
        gpio_set_dir(rgb_pin[i], GPIO_OUT);     //define cada um deles como saida
        gpio_put(rgb_pin[i], false);        //garante que todos serão desligados por padrão
    }
}

void pico_rgb_control(const uint *rgb_pin, int size, int blink_index)
{   
    //apaga todos os leds
    for(int i = 0; i<size; i++)
    {
        gpio_put(rgb_pin[i], false);
    }
    
    //acende apenas o desejado
    gpio_put(rgb_pin[blink_index], true);

}

void pico_rgb_turn_on(const uint *rgb_pin)
{
    for(int i = 0; i < 3; i++)
    {
        gpio_put(rgb_pin[i], true);        //garante que todos serão desligados por padrão
    }
}

void acionar_buzzer() //função que aciona o buzzer
{
    gpio_put(buzzer_pin, true);
    sleep_ms(2000); //tempo que o buzzer ficará ativo
    gpio_put(buzzer_pin, false);
    printf("Buzzer desativado!\n");
}

int main() {
    const uint rgb_led[3] = {RGB_RED,RGB_GREEN,RGB_BLUE};
    char buffer[1024];

    stdio_init_all();
    pico_rgb_init(rgb_led);
    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin, GPIO_OUT);
    scanf("%1024s", buffer);
    
    while (true) {
        printf("\nOPÇÃO: ");
        scanf("%1024s", buffer);
        printf("\nESCRITO: %s\n\n", buffer);
        
        if (!strcmp(buffer, "verde")) {
            pico_rgb_control(rgb_led, sizeof(rgb_led), 1);
            printf("Led verde ativo!\n");
        } else if (!strcmp(buffer, "vermelho")) {
            pico_rgb_control(rgb_led, sizeof(rgb_led), 0);
            printf("Led vermelho ativo!\n");
        } else if(!strcmp(buffer, "azul")){
            pico_rgb_control(rgb_led, sizeof(rgb_led), 2);
            printf("Led azul ativo!\n");
        }else if(!strcmp(buffer, "branco")){  // Combina as 3 cores para acender led com a luz branca
            pico_rgb_turn_on(rgb_led);
            printf("Led branco ativo!\n");
        } else if(!strcmp(buffer, "buzzer")){
            acionar_buzzer();
            printf("Buzzer acionado!\n");
        } else if(!strcmp(buffer, "reset")){
            printf("Ativando modo bootsel...\n");
            sleep_ms(1000); // Espera 1 segundo antes de reiniciar no modo bootset
            reset_usb_boot(0, 0);
        }
        else{
            printf("Comando invalido!\n");
        }
    }
    return 0;
}
