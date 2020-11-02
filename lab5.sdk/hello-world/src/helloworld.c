// Default include statements (included in file generation)
#include <stdio.h>
#include "platform.h"

// Additional include statements (added after file generation)
#include "xparameters.h"
#include "xstatus.h"
#include "xintc.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "xbasic_types.h"
#include "xgpio.h"

// Push button input(s). Data type found in the file: xgpio.h
XGpio input;

// Defined variables found in files: xintc.h, xparameters.h
#define INTC_DEVICE_ID			XPAR_INTC_0_DEVICE_ID
#define INTC_DEVICE_INT_ID		XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_0_IP2INTC_IRPT_INTR
#define BTN_INT					XGPIO_IR_CH2_MASK

// Method that executes when interrupt happens
void DeviceDriverHandler(void *CallbackRef);

// Instance of the interrupt controller
static XIntc InterruptController;

// Sets current status of interrupt as false
volatile static int InterruptProcessed = FALSE;

int main(void)
{
	// Introduction to what the program does
	xil_printf("\nProcessor interrupts triggered via push buttons.\n\n");

	// The following methods can be found in: xintc.h, xil_exception.h, xgpio.h
	XGpio_Initialize(&input,XPAR_GPIO_0_DEVICE_ID);
	XGpio_InterruptEnable(&input, BTN_INT);
	XGpio_InterruptGlobalEnable(&input);

	XIntc_Initialize(&InterruptController, INTC_DEVICE_ID);
	XIntc_SelfTest(&InterruptController);

	XIntc_Connect(&InterruptController, INTC_DEVICE_INT_ID, (XInterruptHandler)DeviceDriverHandler, (void *)0);
	XIntc_Start(&InterruptController, XIN_REAL_MODE);
	XIntc_Enable(&InterruptController, INTC_DEVICE_INT_ID);
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, &InterruptController);
	Xil_ExceptionEnable();

	// While loop (that always executes) that is based on when an interrupt processes
	while(1)
	{
		if(InterruptProcessed)
		{
			break;
		}
	}

	return 0;
}

// "Routine method" that executes when an interrupt occurred
void DeviceDriverHandler(void *CallbackRef)
{
	// If-statement that executes when the value of the push button is 1
	if(XGpio_DiscreteRead(&input,1))
	{
		// Number of interrupts that occurred
		static int numInterrupts = 1;

		// Print statement that tracks the number of interrupts that occurred
		xil_printf("Interrupt ");
		xil_printf("%d",numInterrupts);
		xil_printf(" occurred.\n");
		numInterrupts += 1;
	}
	// Clears the value of the input button back to the masked value (0x1)
	XGpio_InterruptClear(&input, BTN_INT);
}
