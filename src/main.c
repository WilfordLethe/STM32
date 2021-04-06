#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int main(void)
{
#ifdef STM32F1
    rcc_periph_clock_enable(RCC_GPIOB);                                             /* Enable GPIO clock. */
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12); /* Set GPIOB12 as output:2MHz */
#elif STM32F4
    rcc_periph_clock_enable(RCC_GPIOC);                              /* Enable GPIO clock */
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0); /* Set GPIOC0 as output */
    rcc_periph_clock_enable(RCC_GPIOD);                              /* Enable GPIO clock */
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3); /* Set GPIOD3 as output */
#else
    return -1;
#endif

    while (1)
    {
#ifdef STM32F1
        gpio_toggle(GPIOB, GPIO12);
#elif STM32F4
        gpio_toggle(GPIOC, GPIO0);
        gpio_toggle(GPIOD, GPIO3);
#else
        return -1;
#endif
        for (int i = 0; i < 1000000; i++)
        {
            __asm__("nop");
        }
    }
    return 0;
}