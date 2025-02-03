# Tarefa-unidade4
# Projeto de Controle de LEDs com Botão para Raspberry Pi Pico

Este projeto demonstra como controlar três LEDs (vermelho, verde e azul) usando um botão em um Raspberry Pi Pico. Ao pressionar o botão, os três LEDs acendem. Após 3 segundos, o LED azul apaga, então o LED vermelho e depois o LED verde se apagam um a um a cada 3 segundos. Os LEDs só podem ser reacendidos após o último LED (verde) ser apagado e o botão for pressionado novamente.

## Hardware Necessário

*   Raspberry Pi Pico
*   1 botão de pressão
*   3 LEDs (vermelho, verde, azul)
*   3 resistores de 330Ω (para os LEDs)

## Diagrama de Conexão

### Botão

*   Um terminal do botão conectado ao pino GPIO 5 do Raspberry Pi Pico.
*   O outro terminal do botão conectado ao GND (terra).

### LEDs

    *   LED Vermelho: GPIO 12
    *   LED Verde: GPIO 13
    *   LED Azul: GPIO 11


## Como Usar

1.  Conecte o botão e os LEDs conforme as instruções.
2.  Carregue o código no Raspberry Pi Pico.
3.  Ao pressionar o botão:
    *   Todos os LEDs acendem.
    *   Após 3 segundos, o LED azul apaga.
    *   Após mais 3 segundos, o LED vermelho apaga.
    *   Após mais 3 segundos, o LED verde apaga.
    *   O ciclo se reinicia somente após o último LED se apagar e você pressionar o botão novamente.

## Código-Fonte

O código fonte em C está no arquivo `main.c`.

*   **`#include`s:** Inclui as bibliotecas necessárias para o projeto.
*   **Definições de pinos:** Define os pinos GPIO usados para o botão e os LEDs.
*   **Enum `LedState`:** Define os diferentes estados dos LEDs (`LEDS_OFF`, `LEDS_ON`, `RED_OFF`, `GREEN_OFF`, `BLUE_OFF`).
*   **Função `main()`:**
    *   Inicializa os pinos do botão (entrada com pull-up) e LEDs (saídas).
    *   Implementa um loop para ler o estado do botão e controlar os LEDs com estados de acendimento e apagamento sequencial.
    *   Usa as funções `delayed_by_ms` e `time_reached` para controlar os intervalos de tempo.
