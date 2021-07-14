#include "help_funcs.h"

void flashLED(uint8_t led_pin, uint32_t time_on, uint32_t delay_after)
{
    /*
     * Function:  flashLED
     * --------------------
     * Function to flashes an onboard LED
     *    for MCU TM4C123GH6PM using TivaWare.
     *
     * Args:
     * led_pin: Led pin on the board
     * time_on: Time in clocks ticks to keep led on
     * delay_after: Option to add delay after the flash
     */
    GPIOPinWrite(GPIO_PORTF_BASE, led_pin, led_pin);
    SysCtlDelay(time_on);
    GPIOPinWrite(GPIO_PORTF_BASE, led_pin, 0);
    SysCtlDelay(delay_after);
}

void flashAllLED(uint32_t time_on, uint32_t delay_after)
{
    /*
     * Function:  flashAllLED
     * --------------------
     * Function to flash all onboard LEDs (white color)
     *    for MCU TM4C123GH6PM using TivaWare.
     *
     * Args:
     * time_on: Time in clocks ticks to keep leds on
     * delay_after: Option to add delay after the flash
     */
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, BLUE_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);
    SysCtlDelay(time_on);
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, 0);
    SysCtlDelay(delay_after);
}


void configureUART(void)
{
    /*
     * Function:  ConfigureUART
     * --------------------
     * Function to initialize onboard UART.
     *    for MCU TM4C123GH6PM using TivaWare.
     */
    // Enable the GPIO Peripheral used by the UART.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Enable UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Configure GPIO Pins for UART mode.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);
    flashLED(GREEN_LED,1000000,1000000);
}

void configureSSI(uint32_t ui32BitRate, uint32_t ui32DataWidth)
{
    /*
     * Function:  configureSSI
     * --------------------
     * Function to initialize onboard SSI/SPI.
     *    for MCU TM4C123GH6PM using TivaWare.
     *    based on Table 15-1. SSI Signals (64LQFP) page 954
     * Args:
     * ui32BitRate: Communication bit rate
     * ui32DataWidth: Transmitted data width
     */

    SysCtlPeripheralEnable(SDC_GPIO_SYSCTL_PERIPH);
    SysCtlPeripheralEnable(SDC_SSI_SYSCTL_PERIPH);
    GPIOPinConfigure(SDC_SSI_CLK);
    GPIOPinConfigure(SDC_SSI_FSS);
    GPIOPinConfigure(SDC_SSI_RX);
    GPIOPinConfigure(SDC_SSI_TX);
    GPIOPinTypeSSI(SDC_GPIO_PORT_BASE, SDC_SSI_CLK | SDC_SSI_RX | SDC_SSI_TX | SDC_SSI_FSS);
    SSIConfigSetExpClk(SDC_SSI_BASE,SysCtlClockGet(),SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,ui32BitRate,ui32DataWidth);
    SSIEnable(SDC_SSI_BASE);
    flashLED(GREEN_LED,1000000,1000000);
}

void configureLED(void)
{
    /*
     * Function:  configureLED
     * -----------------------
     * Function to initialize onboard leds.
     *    for MCU TM4C123GH6PM using TivaWare.
     */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED);
    flashLED(GREEN_LED,1000000,1000000);
}
