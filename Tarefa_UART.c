#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#define RGB_RED 13
#define RGB_BLUE 12
#define RGB_GREEN 11


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


int main() {
    const uint rgb_led[3] = {RGB_RED,RGB_GREEN,RGB_BLUE};
    char buffer[1024];

    stdio_init_all();
    pico_rgb_init(rgb_led);
    

    while (true) {
        printf("\nOPÇÃO: ");
        scanf("%1024s", buffer);
        printf("\nESCRITO: %s\n\n", buffer);
        
        if (!strcmp(buffer, "verde")) {
            pico_rgb_control(rgb_led, sizeof(rgb_led), 1);
            printf("Led verde ativo!\n");
        } else{
           printf("Comando invalido!\n");
        } 
    }
    return 0;
}
