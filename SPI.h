#ifndef SPI_H_
#define SPI_H_
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
// define what type of SPI you want to use: 1 - using software SPI, 0 - using hardware SPI
//..............................................................................................................
#define USE_SOFTWARE_SPI 0




void init_SPI(void);							//initialize SPI
uint8_t SPI_WriteReadByte( uint8_t data );		//write/read byte to/from nRF
void SPI_WriteByte( uint8_t data );				//write byte to nRF
void SPI_WriteDataBuffer ( uint8_t * data_buffer_out , uint8_t length );								//write to nRF buffer with data
void SPI_WriteReadDataBuffer ( uint8_t * data_buffer_in, uint8_t * data_buffer_out, uint8_t length );	//write/read to/from nRF buffer with data



#endif /* SPI_H_ */









