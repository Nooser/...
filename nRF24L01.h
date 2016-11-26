#ifndef NRF24L01_H_
#define NRF24L01_H_

#include "nRF24L01_memory_map.h"
#include <avr/pgmspace.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//       PIN ASSIGMENT - PRZYDZIA� PIN�W                                                               //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IRQ 	PB2			//IRQ PIN
#define CE  	PB0		    //CE PIN
#define CSN 	PB1		    //Chip select PIN
#define SS 		PB2			//SS set the same as CSN
#define MOSI 	PB3			//MOSI pin
#define MISO 	PB4			//MISO pin
#define SCK 	PB5			//SCK pin


#define IRQ_DDR_PORT DDRB	//direction port
#define IRQ_PORT     PORTB	//output port
#define IRQ_PIN      PINB	//input port

#define CE_DDR_PORT DDRB	//direction port
#define CE_PORT     PORTB	//output port
#define CE_PIN      PINB	//input port

#define CSN_DDR_PORT DDRB	//direction port
#define CSN_PORT     PORTB	//output port
#define CSN_PIN      PINB	//input port

#define SS_DDR_PORT DDRB	//direction port
#define SS_PORT     PORTB	//output port
#define SS_PIN      PINB	//input port

#define MOSI_DDR_PORT DDRB	//direction port
#define MOSI_PORT     PORTB	//output port
#define MOSI_PIN      PINB	//input port

#define MISO_DDR_PORT DDRB	//direction port
#define MISO_PORT     PORTB	//output port
#define MISO_PIN      PINB	//input port

#define SCK_DDR_PORT DDRB	//direction port
#define SCK_PORT     PORTB	//output port
#define SCK_PIN      PINB	//input port



#define NRF_DDR_PORT DDRC	//direction register of port which control nRF power
#define NRF_PORT            PORTC	//output register of port which control nRF power
#define NRF_PIN             PC0		//pin on the output register thah controls nRF power

#define NRF_ON 	NRF_PORT &= ~(1<<NRF_PIN);	//turn on nRF
#define NRF_OFF NRF_PORT |= (1<<NRF_PIN);	//turn off nRF


#define CSN_HIGH CSN_PORT |=  (1<<CSN) 	//make CSN high macro
#define CSN_LOW  CSN_PORT &= ~(1<<CSN)	//make CSN low macro

#define CE_HIGH  CE_PORT |=  (1<<CE)	//make CE high macro
#define CE_LOW   CE_PORT &= ~(1<<CE)	//make CE low macro


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SET TX and RX adresses length																					//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TX_ADDRES_LENGTH 5
#define RX_ADDRES_LENGTH 5

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SET maximum payload size ( 1 - 32 bytes )																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAXIMUM_PAYLOAD_SIZE 32

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// define using IRQ (1 - use IRQ, 0 - don't use IRQ)															//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define USE_IRQ 0



////////////////////////////////////////////////////////////
// INTERRUPTS CONFIGURATOR - Konfigurator przerwa�        //
// 1 - interrupt active       1 - przerwanie aktywne      //
// 0 - interrupt not active   0 - przerwanie wy��czone    //
////////////////////////////////////////////////////////////
#define USE_MAX_RETRANSMISION_IRQ   1
#define USE_END_OF_TRANSMISSION_IRQ 1
#define USE_DATA_READY_TO_READ_IRQ  1


#if USE_MAX_RETRANSMISION_IRQ == 1
#define MAX_RT_MASK (0<<MASK_MAX_RT)
#else
#define MAX_RT_MASK (1<<MASK_MAX_RT)
#endif

#if USE_END_OF_TRANSMISSION_IRQ == 1
#define TX_DS_MASK (0<<MASK_TX_DS)
#else
#define TX_DS_MASK (1<<MASK_TX_DS)
#endif

#if USE_DATA_READY_TO_READ_IRQ == 1
#define RX_DR_MASK (0<<MASK_RX_DR)
#else
#define RX_DR_MASK (1<<MASK_RX_DR)
#endif

#define nRF24L01_CONFIG ( RX_DR_MASK | MAX_RT_MASK | TX_DS_MASK )





///''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
// RX and TX event flags
//........................................................................................................................
extern volatile uint8_t TX_flag;
extern volatile uint8_t RX_flag;

//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
// function declarations
//........................................................................................................................
void nRF_RX_EVENT (void);			      //this function checks if there are data to read and if there is callback function registered.
										  //if there are data avaliable to read this function sends this data to registered calbback function

void register_nRF_RX_Event_Callback ( void ( * callback )( void * nRF_RX_buff , uint8_t len ) ); //this function is used to register RX_EVENT callback function

void nRF_SendDataToAir( char * data ); //this function sends data to to another nRF or nRF's. Length of data payload is calculeted by strlen funcion so
										  //you must send data in ASCII format
uint8_t nRF_Data_Ready(void);			  //this function is used when IRQ are disabled. It checks if there any data to read
void Initialize_INTERRUPT_For_nRF(void);  //this function is used to initlialization of external interrupt for nRF
void nRF_init( void );                                                 //Initialize NRF24l01
void nRF_Config_Register(uint8_t register_name, uint8_t value);        //WRITE SOMETHING TO NRF REGISTER
void nRF_SET_Transmitter_Adres(const char * addres);				   //this function sets transmitter addres
void nRF_SET_Reciver_Addres( uint8_t data_pipe, const char * addres ); //this function sets reciver addres of choosen datapipe
uint8_t nRF_Read_One_Byte_From_Register(uint8_t register_name);		   //this function returns value of register given by attribute
void nRF_Set_Retransmission_Time_And_Ammount (uint8_t time, uint8_t ammount); //this function sets time beetwen retransmissions and ammount of them
void nRF_TX_Power_Up(void);				  //this function turns on TX mode
void nRF_RX_Power_Up(void);				  //this function turns on RX mode
void nRF_Power_Down(void);			      //this funtion turns on Power_down mode
void nRF_Set_Channel( uint8_t channel );  //this function sets channel ( 0 to 127 )
void nRF_Clear_TX (void);				  //this function clears TX fifo
void nRF_Clear_RX (void);				  //this function clears RX fifo


#endif /* NRF24L01_H_ */












