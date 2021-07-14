//#ifndef SSI_DEFS_H_
//#define SSI_DEFS_H_

#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

/*
 * Definitions for SSI/SPI Communication
 * ------------------------------------
 *    for MCU TM4C123GH6PM in TivaWare.
 *    based on Table 15-1. SSI Signals (64LQFP) page 954
 */

/* SSI/SPI Interface (0/1/2/3) */
#define SSI 0

/* Peripheral definitions board */

#if SSI==0
    // GPIO for SSI0 pins
    #define SDC_SSI_BASE            SSI0_BASE
    #define SDC_SSI_SYSCTL_PERIPH   SYSCTL_PERIPH_SSI0
    #define SDC_GPIO_PORT_BASE      GPIO_PORTA_BASE
    #define SDC_GPIO_SYSCTL_PERIPH  SYSCTL_PERIPH_GPIOA
    #define SDC_SSI_CLK             GPIO_PIN_2
    #define SDC_SSI_FSS             GPIO_PIN_3
    #define SDC_SSI_RX              GPIO_PIN_4
    #define SDC_SSI_TX              GPIO_PIN_5

#elif SSI==1
    // GPIO for SSI1 pins
    #define SDC_SSI_BASE            SSI1_BASE
    #define SDC_SSI_SYSCTL_PERIPH   SYSCTL_PERIPH_SSI1
    #define SDC_GPIO_PORT_BASE      GPIO_PORTF_BASE
    #define SDC_GPIO_SYSCTL_PERIPH  SYSCTL_PERIPH_GPIOF
    #define SDC_SSI_CLK             GPIO_PIN_2
    #define SDC_SSI_FSS             GPIO_PIN_3
    #define SDC_SSI_RX              GPIO_PIN_0
    #define SDC_SSI_TX              GPIO_PIN_1

#elif SSI==2
    // GPIO for SSI2 pins
    #define SDC_SSI_BASE            SSI2_BASE
    #define SDC_SSI_SYSCTL_PERIPH   SYSCTL_PERIPH_SSI2
    #define SDC_GPIO_PORT_BASE      GPIO_PORTB_BASE
    #define SDC_GPIO_SYSCTL_PERIPH  SYSCTL_PERIPH_GPIOB
    #define SDC_SSI_CLK             GPIO_PIN_4
    #define SDC_SSI_FSS             GPIO_PIN_5
    #define SDC_SSI_RX              GPIO_PIN_6
    #define SDC_SSI_TX              GPIO_PIN_7

#elif SSI==3
    // GPIO for SSI3 pins
    #define SDC_SSI_BASE            SSI3_BASE
    #define SDC_SSI_SYSCTL_PERIPH   SYSCTL_PERIPH_SSI3
    #define SDC_GPIO_PORT_BASE      GPIO_PORTD_BASE
    #define SDC_GPIO_SYSCTL_PERIPH  SYSCTL_PERIPH_GPIOD
    #define SDC_SSI_CLK             GPIO_PIN_0
    #define SDC_SSI_FSS             GPIO_PIN_1
    #define SDC_SSI_RX              GPIO_PIN_2
    #define SDC_SSI_TX              GPIO_PIN_3

#endif

#define SDC_SSI_PINS            (SDC_SSI_TX | SDC_SSI_RX | SDC_SSI_CLK | SDC_SSI_FSS)






//#endif /* SSI_DEFS_H_ */
