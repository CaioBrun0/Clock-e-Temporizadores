# README - Repositório de Atividades

Este repositório contém duas atividades desenvolvidas para a placa Raspberry Pi Pico utilizando a biblioteca `pico/stdlib.h` e o `hardware/timer.h`. Ambas as atividades envolvem o controle de LEDs com temporizações e interação com botões.

## Atividade 1 - Sequenciamento de LEDs com Temporizador

### Descrição
A Atividade 1 implementa um sistema no qual três LEDs (vermelho, amarelo e verde) piscam sequencialmente a cada 3 segundos. O comportamento é gerenciado por uma função de callback do temporizador.

### Funcionamento
- Inicialmente, todos os LEDs estão apagados.
- A cada 3 segundos, apenas um LED é ligado, seguindo a ordem: vermelho → amarelo → verde.
- O sistema repete esse ciclo indefinidamente.
- Durante a execução, mensagens de log são exibidas no console para indicar o tempo transcorrido.

### Componentes Utilizados
- LEDs: Vermelho (GPIO 13), Amarelo (GPIO 12), Verde (GPIO 11).
- Temporizador para acionar a função de callback periodicamente.

### Estrutura do Código
- A função `repeating_timer_callback()` é chamada a cada 3 segundos para alterar o estado dos LEDs.
- O `main()` inicializa os pinos dos LEDs e registra a função de callback.
- Uma mensagem é impressa a cada segundo para monitoramento.
- O módulo `testes.h` é chamado para a execução de testes automáticos.

## Atividade 2 - Controle de LEDs via Botão

### Descrição
A Atividade 2 implementa um sistema em que um botão é utilizado para acionar três LEDs. Uma vez ativado, os LEDs são desligados um a um em intervalos de 3 segundos, respeitando um estado sequencial.

### Funcionamento
- Quando o botão é pressionado, os três LEDs são acesos simultaneamente.
- Um temporizador de callback é utilizado para desligar os LEDs um a um a cada 3 segundos.
- Enquanto o processo de desligamento estiver em andamento, pressionar o botão não tem efeito.
- Ao final do ciclo, o sistema permite uma nova interação pelo botão.

### Componentes Utilizados
- LEDs: Azul (GPIO 12), Vermelho (GPIO 13), Verde (GPIO 11).
- Botão (GPIO 5) para ativar os LEDs.
- Temporizador para desligar os LEDs sequencialmente.
- Variável `led_active` para evitar acionamento durante a execução do ciclo.

### Estrutura do Código
- A função `turn_on_callback()` é responsável por desligar os LEDs um a um.
- O `main()` inicializa os LEDs e o botão, verificando continuamente se ele foi pressionado.
- O módulo `testes.h` é chamado para a execução de testes automáticos.
- O sistema impede que o botão seja acionado novamente enquanto a sequência de desligamento estiver em execução.

## Como Executar
1. Compile o código para a Raspberry Pi Pico.
2. Carregue o binário na placa.
3. Para a Atividade 1, observe a sequência de LEDs piscando automaticamente.
4. Para a Atividade 2, pressione o botão para iniciar o ciclo de acendimento e desligamento dos LEDs.

## Observações
- Certifique-se de que a biblioteca `pico-sdk` esteja corretamente configurada no ambiente de desenvolvimento.
- O código foi estruturado para ser extensível e pode ser modificado para ajustar tempos de temporização ou incluir novos comportamentos.

