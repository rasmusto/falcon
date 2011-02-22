static int putcharDebug (char c, FILE *stream) {
	if (c == '\n')
		putcharDebug('\r', stream);
 
    // Wait for the transmit buffer to be empty
    while ( !( USARTC0.STATUS & USART_DREIF_bm) );
 
    // Put our character into the transmit buffer
    USARTC0.DATA = c; 
 
    return 0;
}


// map putchar to mystdout for use with printf (stdout needs to be set to &debug in main)
static int putcharDebug (char c, FILE *stream);
static void initUarts (void);
static FILE debug = FDEV_SETUP_STREAM (putcharDebug, NULL, _FDEV_SETUP_WRITE);

static void initUarts (void) {
    // Set the TxD pin high - set PORTD DIR register bit 3 to 1
    PORTC.OUTSET = PIN3_bm;
 
    // Set the TxD pin as an output - set PORTD OUT register bit 3 to 1
    PORTC.DIRSET = PIN3_bm;
 
    // BSEL = 51 so at 32mhz clock, baud rate should be 38400
	
    USARTC0.BAUDCTRLB = 0;			// BSCALE = 0 as well
    USARTC0.BAUDCTRLA = 51;
 
    // Set mode of operation
    USARTC0.CTRLA = 0;				// no interrupts please
    USARTC0.CTRLC = 0x03;			// async, no parity, 8 bit data, 1 stop bit
 
    // Enable transmitter only
    USARTC0.CTRLB = USART_TXEN_bm;
}

	//~ ISR(ADCA_CH3_vect) {
		//~ ADCA.CH3.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
		//~ if (samplingGroup == 0) {
			//~ senseValues[0] = ADCA.CH0.RES;
			//~ senseValues[1] = ADCA.CH1.RES;
			//~ senseValues[2] = ADCA.CH2.RES;
			//~ senseValues[3] = ADCA.CH3.RES;
		//~ }
		//~ else {
			//~ senseValues[4] = ADCA.CH0.RES;
			//~ senseValues[5] = ADCA.CH1.RES;
			//~ senseValues[6] = ADCA.CH2.RES;
			//~ senseValues[7] = ADCA.CH3.RES;
		//~ }
		//~ 
		//~ // Flip between sampling groups for adcA, because we need to sample all 8 pins and there are only 4 adc channels
		//~ if (samplingGroup == 0) {
			//~ // Set input to the channels in ADC A to be PIN 4, 5, 6 and 7
			//~ ADC_Ch_InputMux_Config(&(ADCA.CH0), ADC_CH_MUXPOS_PIN4_gc, ADC_CH_MUXPOS_PIN4_gc);
			//~ ADC_Ch_InputMux_Config(&(ADCA.CH1), ADC_CH_MUXPOS_PIN5_gc, ADC_CH_MUXPOS_PIN5_gc);
			//~ ADC_Ch_InputMux_Config(&(ADCA.CH2), ADC_CH_MUXPOS_PIN6_gc, ADC_CH_MUXPOS_PIN6_gc);
			//~ ADC_Ch_InputMux_Config(&(ADCA.CH3), ADC_CH_MUXPOS_PIN7_gc, ADC_CH_MUXPOS_PIN7_gc);
			//~ samplingGroup = 1; // keep track of sampleingGroup.  Group 1 = Pins 4,5,6,7
		//~ } else {
			//~ // Set input to the channels in ADC A to be PIN 0, 1, 2 and 3
			//~ ADC_Ch_InputMux_Config(&(ADCA.CH0), ADC_CH_MUXPOS_PIN0_gc, ADC_CH_MUXPOS_PIN0_gc);
			//~ ADC_Ch_InputMux_Config(&(ADCA.CH1), ADC_CH_MUXPOS_PIN1_gc, ADC_CH_MUXPOS_PIN1_gc);
			//~ ADC_Ch_InputMux_Config(&(ADCA.CH2), ADC_CH_MUXPOS_PIN2_gc, ADC_CH_MUXPOS_PIN2_gc);
			//~ ADC_Ch_InputMux_Config(&(ADCA.CH3), ADC_CH_MUXPOS_PIN3_gc, ADC_CH_MUXPOS_PIN3_gc);
			//~ samplingGroup = 0; // keep track of sampleingGroup.  Group 1 = Pins 0,1,2,3
		//~ }
	//~ }
//~ 
	//~ ISR(ADCB_CH0_vect) {
		//~ ADCB.CH0.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
		//~ senseValues[8] = ADCB.CH0.RES-adcOffsetB;
	//~ }
//~ 
	//~ ISR(ADCB_CH1_vect) {
		//~ ADCB.CH1.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
		//~ senseValues[9] = ADCB.CH1.RES-adcOffsetB;
	//~ }
//~ 
	//~ ISR(ADCB_CH2_vect) {
		//~ ADCB.CH2.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
		//~ senseValues[10] = ADCB.CH2.RES-adcOffsetB;
	//~ }
//~ 
	//~ ISR(ADCB_CH3_vect) {
		//~ ADCB.CH3.INTFLAGS = ADC_CH_CHIF_bm; // Clear interrupt flag
		//~ senseValues[11] = ADCB.CH3.RES-adcOffsetB;
	//~ }
