#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "uart.h"
#include "nRF24L01.h"


void moja_funkcja ( void * nRF_RX_buff , uint8_t len );
volatile uint16_t timer100ms;

int main (void)
{
	//flagi pomocnicze
	uint8_t flaga1, flaga2;
	flaga1 = 0;
	flaga2 = 0;

	//dioda do debugowania
	//DDRA |= (1<<PA0);
	//PORTA |= (1<<PA0);

	//inicjalizacja uarta
    USART_Init(__UBRR);

	//inicjalizacja nRFa
    nRF_init();
    register_nRF_RX_Event_Callback(moja_funkcja);


    //inicjalizacja timera programowego co 1ms
    TCCR2 |= (1<<WGM21) | (1<<CS22) |  (1<<CS20);
    TIMSK |= (1<<OCIE2);
    OCR2 = 156;

   	//zezwolenie na przerwania
    sei();

    nRF_RX_Power_Up(); //odpalamy nRFA!
	while(1)
	{
		    if(timer100ms == 0)
			{
				timer100ms = 100 ;
				flaga1 ^= 1;
				flaga2 = 0;
				//PORTA ^= (1<<PA0);
			}

			if ( (flaga1==1) && (flaga2 == 0) )
			{
				nRF_SendDataToAir("ZGAS_LED");
				flaga2=1;
			}
			if ( (flaga1==0) && (flaga2 == 0) )
			{
				nRF_SendDataToAir("ZAPAL_LED");
				flaga2=1;
			}
           
			nRF_RX_EVENT();
	}
}


void moja_funkcja ( void * nRF_RX_buff, uint8_t len )
{
	
char buffer_for_itoa[4] = { 0, 0, 0, 0};
itoa( len, buffer_for_itoa, 10 );
uart_puts("ODEBRANO BAJTOW: ");
uart_puts(buffer_for_itoa);
uart_puts( (char *) nRF_RX_buff );

}

ISR(TIMER2_COMP_vect)
{
	if(timer100ms) timer100ms--;
}
