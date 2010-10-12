#define F_CPU 32000000UL
#include "dma_driver.h"

//#include "/usr/lib/avr/include/avr/iox128a3.h" //for tab completion :3

/*! Size of one memory block. */
#define MEM_BLOCK_SIZE   (1)

/*! Memory block count. */
#define MEM_BLOCK_COUNT (25)

/*
volatile DMA_CH_t * channel0;
volatile DMA_CH_t * channel1;
volatile DMA_CH_t * channel2;
volatile DMA_CH_t * channel3;

static USART_t * motor1USART = &USARTD0;
static USART_t * motor2USART = &USARTD1;
static USART_t * motor3USART = &USARTC1;
static USART_t * motor4USART = &USARTC0;
static USART_t * debugUSART  = &USARTF0;
*/

bool DMAWriteUSART(char* packet, uint8_t numBytes, USART_t* uart, DMA_CH_t * dmaChannel);

/*
int main (void) 
{	
    //initMotorUarts();
    //initIMUUart();
    //initDebugUart();
    //initCtrlUart();

    PORTA.DIR = 0xFF;
    PORTB.DIR = 0xFF;
    PORTC.DIR = 0xFF;
    PORTD.DIR = 0xFF;
    PORTE.DIR = 0xFF;
    PORTF.DIR = 0xFF;

    sei();

    //DMA TEST
    uint32_t index;

    PMIC.CTRL |= PMIC_MEDLVLEX_bm; //what is this?

    channel0 = &DMA.CH0;
    channel1 = &DMA.CH1;
    channel2 = &DMA.CH2;
    channel3 = &DMA.CH3;

    uint8_t packet[25] = "DMA TEST 1 2 3 4 5 6 7 8 \n";
    while(1)
    {
        DMAWriteUSART(packet, 18, debugUSART, channel0);
    }
}
*/

bool DMAWriteUSART(char* packet, uint8_t numBytes, USART_t* usart, DMA_CH_t * dmaChannel)
{
    DMA.CTRL |= DMA_CH_ENABLE_bm;                   //Enable controller
    dmaChannel->CTRLA |= DMA_CH_SINGLE_bm;          //Set single shot mode
    dmaChannel->CTRLA |= DMA_CH_BURSTLEN_1BYTE_gc;  //Cycle stealing mode
    dmaChannel->ADDRCTRL |= DMA_CH_SRCDIR_INC_gc;   //Increment SRC
    dmaChannel->ADDRCTRL |= DMA_CH_DESTDIR_FIXED_gc;//Fixed DEST
    dmaChannel->TRIGSRC |= DMA_CH_TRIGSRC_OFF_gc;   //Manual trigger
    dmaChannel->TRFCNT = 25;                        //Block size 25

    dmaChannel->SRCADDR0 = (( (uint32_t) packet) >> 0*8 ) & 0xFF;
    dmaChannel->SRCADDR1 = (( (uint32_t) packet) >> 1*8 ) & 0xFF;
    dmaChannel->SRCADDR2 = (( (uint32_t) packet) >> 2*8 ) & 0xFF;

    dmaChannel->DESTADDR0 = (( (uint32_t) usart->DATA) >> 0*8 ) & 0xFF;
    dmaChannel->DESTADDR1 = (( (uint32_t) usart->DATA) >> 1*8 ) & 0xFF;
    dmaChannel->DESTADDR2 = (( (uint32_t) usart->DATA) >> 2*8 ) & 0xFF;

    DMA.CH0.TRIGSRC = 0xAC; //USARTF0 data buffer empty triggers transfer

    dmaChannel->CTRLA |= DMA_CH_ENABLE_bm;          //Enable channel

    /*
       DMA_EnableChannel(dmaChannel);
       DMA_SetupBlock( dmaChannel,                            //DMA channel
       packet,                             //Source address
       DMA_CH_SRCRELOAD_TRANSACTION_gc,	//Reload the source destination after each transaction
       DMA_CH_SRCDIR_INC_gc,				//Source address is increasing (data is in an array)
       uart->DATA,			         		//Destination address
       DMA_CH_DESTRELOAD_BLOCK_gc,			//Reload the destination address after each block xfer
       DMA_CH_DESTDIR_FIXED_gc,			//Always write to the uart data buffer
       (uint16_t)1,						//Each block is 1 byte
       DMA_CH_BURSTLEN_1BYTE_gc,			//1 byte per burst
       numBytes,							//25 total blocks
       true ); 							//Use repeat (25 times)
       DMA_SetIntLevel(dmaChannel, DMA_CH_TRNINTLVL_MED_gc, DMA_CH_ERRINTLVL_OFF_gc);

       DMA_StartTransfer(dmaChannel);

*/
}

ISR(DMA_CH0_vect)
{
}

ISR(DMA_CH1_vect)
{
}

ISR(DMA_CH2_vect)
{
}

ISR(DMA_CH3_vect)
{
}
