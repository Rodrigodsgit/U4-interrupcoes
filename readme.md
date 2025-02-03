<table align="center">
  <tr>
    <td><img src="image.png" width="100"></td>
    <td align="center">
      <b>Embarca Tech - CEPEDI</b><br>
      Capacitação Inicial em Sistemas Embarcados<br>
      U1 - Introdução à Educação a Distância<br>
      <b>Discente - Rodrigo Damasceno Sampaio (Grupo 9)</b>
    </td>
    <td><img src="image2.png" width="100"></td>
  </tr>
</table>



# LED Matrix Display - RP2040

Este é um projeto para o microcontrolador **RP2040**, utilizando a placa **BitDogLab**, que exibe números de 0 a 9 em uma **matriz de LEDs WS2812 (5x5)**. Os números são alternados através de **botões físicos**, utilizando **interrupções e debounce** para um funcionamento eficiente e preciso.

---

## ✨ **Funcionalidades**
- ✅ Exibição de **números de 0 a 9** em uma **matriz 5x5 de LEDs WS2812**.
- ✅ Controle da exibição dos números através de **botões físicos**:
  - **BTN_A** (GPIO 5) → **Incrementa** o número.
  - **BTN_B** (GPIO 6) → **Decrementa** o número.
- ✅ **Pisca um LED vermelho (GPIO 13) 5 vezes por segundo**.
- ✅ **Uso de interrupções (IRQ) nos botões**, evitando a necessidade de verificação contínua no loop principal.
- ✅ **Implementação de debounce por software**, prevenindo múltiplos acionamentos involuntários do botão.

---

## 🛠 **Tecnologias Utilizadas**
Este projeto foi desenvolvido utilizando:
- **Linguagem C** (para programação do RP2040)
- **Microcontrolador RP2040** (usado na placa **BitDogLab**)
- **PIO (Programmable I/O) do RP2040** (para comunicação com LEDs WS2812)
- **WS2812 RGB LEDs** (endereçáveis, matriz 5x5)
- **Interrupções (IRQ)** para detectar pressionamento de botões
- **Debounce por software** para evitar leituras erradas dos botões
- **CMake** para compilação e build do firmware

---

## 📌 **Conceitos Importantes**

### 🔹 **Interrupções (IRQ)**
As **interrupções** permitem que o microcontrolador **detecte eventos automaticamente**, sem precisar verificar manualmente os botões o tempo todo. Isso deixa o código mais eficiente.


📌 **Como funciona no código?**  
No nosso projeto, configuramos interrupções nos botões **BTN_A** e **BTN_B**. Quando um botão é pressionado, o código principal **pausa momentaneamente** e executa uma função para tratar o evento:

```c
gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &button_interrupt_handler);
gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &button_interrupt_handler);

```


## 📌 **Conclusão**

Este projeto demonstrou o uso eficiente do RP2040 para controlar uma matriz de LEDs WS2812 de maneira responsiva e otimizada. Com a implementação de interrupções (IRQ), garantimos que os botões físicos funcionem sem a necessidade de verificações constantes no loop principal, tornando o código mais eficiente. Além disso, o debounce por software evita múltiplas leituras indevidas, proporcionando uma experiência de uso confiável.

O sistema permite a exibição de números de 0 a 9, utilizando botões para incrementar e decrementar a contagem, enquanto um LED vermelho pisca 5 vezes por segundo para indicar que o sistema está ativo. Também exploramos conceitos essenciais como PIO (Programmable I/O) para LEDs WS2812, tornando o código modular e fácil de expandir.


<p align="center">
  <img src="placa.gif" width="300">
</p>

---