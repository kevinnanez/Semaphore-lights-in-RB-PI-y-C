/*

    Part of the Raspberry-Pi Bare Metal Tutorials
    Copyright (c) 2013, Brian Sidebotham
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
        this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.

*/

/*
    Interrupts example, show how to use the interrupt controller and to load
    the vector table at runtime.
*/

#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"
#include "rpi-armtimer.h"
#include "rpi-systimer.h"
#include "rpi-interrupts.h"
#include "sem.h"

void set_output( gpfsel, gpfbit )
{
    RPI_GetGpio()->gpfsel |= (1 << gpfbit);
}

void led_off( gpio_bit )
{
    do { RPI_GetGpio()->LED_GPCLR = ( 1 <<  gpio_bit ); } while( 0 );
}

void led_on( gpio_bit )
{
    do { RPI_GetGpio()->LED_GPSET = ( 1 <<  gpio_bit ); } while( 0 );
}

unsigned int run_modo( const ciclo_t secAct[] )
{
    unsigned int i = 0;
    unsigned int safe = 1;

	while(safe){
		aux = 11111111 && secAct[i].estados;
		if(aux == 00001001 || aux == 00001010 || aux == 00010001 || aux == 00000000){
            safe = 0;
		}else
			i++;
	}
    return safe;
}

/** Main function - we'll never return from here */
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    /* Write 1 to the LED init nibble in the Function Select GPIO
       peripheral register to enable LED pin as an output */

    /* inicializar todo en cero */
    RPI_GetGpio()->LED_GPFSEL0 = 0;
    RPI_GetGpio()->LED_GPFSEL1 = 0;
    RPI_GetGpio()->LED_GPFSEL2 = 0;

    /* establecer las salidas */
    set_output( LED_GPFSEL1, LED_GPFBIT_C1R );
    set_output( LED_GPFSEL1, LED_GPFBIT_C1A );
    set_output( LED_GPFSEL2, LED_GPFBIT_C1V );
    set_output( LED_GPFSEL0, LED_GPFBIT_C2R );
    set_output( LED_GPFSEL2, LED_GPFBIT_C2A );
    set_output( LED_GPFSEL1, LED_GPFBIT_C2V );

    /* Enable the timer interrupt IRQ */
    RPI_GetIrqController()->Enable_Basic_IRQs = RPI_BASIC_ARM_TIMER_IRQ;


    /* 
        Despues de esto debemos apuntar a un modo (1 de los 3),
        iterar en las secuencias.
        Por cada secuencia, hacemos una mascara de los bits para saber
        cual led esta prendido o apagado.
        Si los leds corresponden a una secuencia no permitida
        entonces apuntar al modo de emergencia. Si no, seteamos el tiempo con RPI_GetArmTimer()->Load y
        llamamos a las funciones para prender y apagar los correspondientes leds.
        Verificamos el estado del switch (si esta encendido, apuntamos al siguiente modo)

    */

/*   
	Pseudocodigo 
	loop
	pulso el sw
		entro al modo n
		if (!run_modo(modo_n[]))
			modo de emergencia hasta q pulse el sw

            
	RPI_algo()->Modo = modo_0; 			//Esto tiene q ser al azar entre 0 y 2

	led_on( SW_GPIO_BITS );		//Pulso el switch
	RPI_algo->Modo = modo_1			//Paso al siguiente modo, no necesariamente modo_1
	led_off( SW_GPIO_BITS );		//Suelto de switch

*/
    /* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x400 */
    RPI_GetArmTimer()->Load = 1000000;//0x400;

    /* Setup the ARM Timer */
    RPI_GetArmTimer()->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_1;

    /* Enable interrupts! */
    _enable_interrupts();

    /* Never exit as there is no OS to exit to! */
    while(1)
    {

    }
}
