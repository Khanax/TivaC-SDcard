#include <string.h>
#include <stdio.h>
#include "help_funcs.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "ff.h"
#include "diskio.h"
#include "utils/cmdline.h"
#include "driverlib/rom.h"

void SysTickHandler(void)
{
    /*
     * Function:  SysTickHandler
     * --------------------
     * Function for systick handler for FatFs library
     *    for MCU TM4C123GH6PM in TivaWare.
     */
    ROM_SysTickIntDisable();
    disk_timerproc();
    ROM_SysTickIntEnable();
}
// mount the file system, using logical disk 0.
FATFS fatfs;
FIL fil;
FRESULT MOUNT;
UINT br, bw;
const TCHAR *path = "LOG1.txt";

int main(void)
{
    unsigned long i;
	//
    // Set the system clock to run at 50MHz from the PLL.
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

	// Configure the systick timer for a 100Hz interrupt. required by the FatFs driver.
    ROM_SysTickPeriodSet(ROM_SysCtlClockGet() / 100);
    SysTickIntRegister(SysTickHandler);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();

    // enable interrupts
    ROM_IntMasterEnable();

    // initialize LEDs for debug but before UART
    configureLED();

    // initialize UART for console I/O
    configureUART();
    UARTprintf("$> Initialized UART Interface\n");
    UARTprintf("$> Initialized Onboard LEDs\n");
    
    // initialize SPI0 for serial communication
    UARTprintf("$> Initializing Synchronous Serial Interface: %u\n",SSI);
    configureSSI(1000000,8);


    // Mount the disk with number 0 (SD card)
    MOUNT = f_mount(0, &fatfs);

    if(MOUNT != FR_OK)
    {
        // Mount has failed and display code on UART
        UARTprintf("$> Mount failed with error code: %d\n",MOUNT);
        return 0;
    }
    else
    {
        // Mount was successful
    	UARTprintf("$> Mount success!\n");
    }
    const TCHAR* tstr = "Hello World, I am the Programmer";

    MOUNT = f_open(&fil, path, FA_CREATE_ALWAYS | FA_WRITE);
    if(MOUNT != FR_OK)
    {
    	UARTprintf("$> Opening of file failed with error code: %d\n",MOUNT);
    	flashLED(RED_LED,1000000,1000000);
        return 0;
    }
    else
    {
    	UARTprintf("$> New file created\n");
    	flashLED(BLUE_LED,1000000,1000000);
    }
    UARTprintf("$> Writing to file\n");

    for(i = 0 ; i < 1; i++)
    {
        MOUNT = f_write(&fil, tstr, strlen((const char *)tstr), &bw);
    	if(MOUNT != FR_OK)
    	{
    	    // File write has failed and display code on UART
    		UARTprintf("$> Writing failed with error code: %d\n",MOUNT);
    		flashLED(RED_LED,1000000,1000000);
    		return 0;
    	}
    }
    UARTprintf("$> Writing completed successfully\n");
    // Closing file and unmounting
    f_close(&fil);
    f_mount(0, NULL);
    // Flashing all leds to signal the end of the program
    flashAllLED(1000000,1000000);
    // loop forever
    while(1){}
}
