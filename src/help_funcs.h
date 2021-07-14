#ifndef HELP_FUNCS_H_
#define HELP_FUNCS_H_

#include <stdint.h>
#include <stdbool.h>
#include "ssi_defs.h"
#include "inc/hw_ssi.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/ssi.h"

// Defines for onboard LEDs. used for debugging
#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

void flashLED(uint8_t led_pin, uint32_t time_on, uint32_t delay_after);
void flashAllLED(uint32_t time_on, uint32_t delay_after);
void configureUART(void);
void configureSSI(uint32_t ui32BitRate, uint32_t ui32DataWidth);
void configureLED(void);

#endif
