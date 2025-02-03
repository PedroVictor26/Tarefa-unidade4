#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definições dos pinos GPIO
#define BUTTON_PIN 5 // GPIO para o botão
#define LED_RED 12    // GPIO para o LED vermelho
#define LED_GREEN 13  // GPIO para o LED verde
#define LED_BLUE 11   // GPIO para o LED azul

// Estados dos LEDs
enum LedState
{
    LEDS_OFF,
    LEDS_ON,
    RED_OFF,
    GREEN_OFF,
    BLUE_OFF
};

int main()
{
    stdio_init_all();

    // Inicializa os pinos GPIO como entrada para o botão e saídas para os LEDs
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Habilita o pull-up interno para o botão

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    enum LedState current_state = LEDS_OFF;
    bool button_pressed = false;
    absolute_time_t next_action_time;

    while (true)
    {
        // Lê o estado do botão
        bool button_state = gpio_get(BUTTON_PIN);

        // Verificando se o botão foi pressionado
        if (button_state == false && !button_pressed)
        {
            button_pressed = true;
        }
        else if (button_state == true && button_pressed)
        {
            button_pressed = false;
        }

        switch (current_state)
        {
        case LEDS_OFF:
            if (button_pressed && button_state == false)
            {
                gpio_put(LED_RED, 1);   // Acende o LED vermelho
                gpio_put(LED_GREEN, 1); // Acende o LED verde
                gpio_put(LED_BLUE, 1);  // Acende o LED azul

                current_state = LEDS_ON;                                     // Transição para o próximo estado
                next_action_time = delayed_by_ms(get_absolute_time(), 3000); // Define o tempo para a próxima ação
            }
            break;

        case LEDS_ON:
            if (time_reached(next_action_time))
            {
                gpio_put(LED_BLUE, 0);                                        // Desliga o LED azul
                current_state = RED_OFF;                                     // Transição para o próximo estado
                next_action_time = delayed_by_ms(get_absolute_time(), 3000); // Define o tempo para a próxima ação
            }
            break;

        case RED_OFF:
            if (time_reached(next_action_time))
            {
                gpio_put(LED_RED, 0); // Desliga o LED vermelho
                current_state = GREEN_OFF;
                next_action_time = delayed_by_ms(get_absolute_time(), 3000); // Define o tempo para a próxima ação
            }
            break;

        case GREEN_OFF:
            if (time_reached(next_action_time))
            {
                gpio_put(LED_GREEN, 0); // Desliga o LED verde
                current_state = BLUE_OFF;
                next_action_time = delayed_by_ms(get_absolute_time(), 3000); // Define o tempo para a próxima ação
            }
            break;

        case BLUE_OFF:
            if (button_pressed && button_state == false)
            {
                gpio_put(LED_RED, 1);   // Acende o LED vermelho
                gpio_put(LED_GREEN, 1); // Acende o LED verde
                gpio_put(LED_BLUE, 1);  // Acende o LED azul

                current_state = LEDS_ON;                                     // Transição para o próximo estado
                next_action_time = delayed_by_ms(get_absolute_time(), 3000); // Define o tempo para a próxima ação
            }
            break;
        }
    }

    return 0;
}