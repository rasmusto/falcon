// here is the pinout of the motor phases and sense lines for reference

//~ PORTE:
	//~ AH1
	//~ AL1
	//~ BH1
	//~ BL1
	//~ CH1
	//~ CL1
	//~ AH2
	//~ AL2
//~ 
//~ PORTF:
	//~ BH2
	//~ BL2
	//~ CH2
	//~ CL2
	//~ AH3
	//~ AL3
	//~ BH3
	//~ BL3
//~ 
//~ PORTD:
	//~ CH3
	//~ CL3
	//~ AH4
	//~ AL4
	//~ BH4
	//~ BL4
	//~ CH4
	//~ CL4
	
// ADCA:
	//~ A1
	//~ B1
	//~ C1
	//~ A2
	//~ B2
	//~ C2
	//~ A3
	//~ B3
	
// ADCB:
	//~ C3
	//~ A4
	//~ B4
	//~ C4

// Motor 1

#define SET_PHASE_STATE_0_MOT1() \
	/* A PWM, B low, C float */ \
								\
	phaseOutputsEHigh &= 0b11000000; \
	phaseOutputsEHigh |= 0b00000001; \
									\
	phaseOutputsELow &= 0b11000000; \
	phaseOutputsELow |= 0b00000010; \
									\
	PORTE.OUTCLR = 0b00111100; /* set b1 floating -- important to do this in this order to avoid shoot through!! (and set c1 floating)  */ \
	PORTE.OUTSET = 0b00001000; /* set b1 low */

#define SET_PHASE_STATE_1_MOT1() \
	/* A PWM, B float, C low */ \
								\
	phaseOutputsEHigh &= 0b11000000; \
	phaseOutputsEHigh |= 0b00000001; \
									\
	phaseOutputsELow &= 0b11000000; \
	phaseOutputsELow |= 0b00000010; \
									\
	PORTE.OUTCLR = 0b00111100; /* set c1 floating -- important to do this in this order to avoid shoot through!! (and set b1 floating) */ \
	PORTE.OUTSET = 0b00100000; /* set c1 low */
	

#define SET_PHASE_STATE_2_MOT1() \
	/* A float, B PWM, C low */ \
								\
	phaseOutputsEHigh &= 0b11000000; \
	phaseOutputsEHigh |= 0b00000100; \
									 \
	phaseOutputsELow &= 0b11000000;  \
	phaseOutputsELow |= 0b00001000;  \
									 \
	PORTE.OUTCLR = 0b00110011; /* set c1 and a1 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTE.OUTSET = 0b00100000; /* set c1 low */ \

#define SET_PHASE_STATE_3_MOT1() \
	/* A low, B PWM, C float */ \
								\
	phaseOutputsEHigh &= 0b11000000; \
	phaseOutputsEHigh |= 0b00000100; \
									 \
	phaseOutputsELow &= 0b11000000;  \
	phaseOutputsELow |= 0b00001000;  \
									\
	PORTE.OUTCLR = 0b00110011; /* set a1 and c1 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTE.OUTSET = 0b00000010; /* set a1 low */ \

#define SET_PHASE_STATE_4_MOT1() \
	/* A low, B float, C PWM */ \
									\
	phaseOutputsEHigh &= 0b11000000; \
	phaseOutputsEHigh |= 0b00010000; \
									\
	phaseOutputsELow &= 0b11000000; \
	phaseOutputsELow |= 0b00100000; \
									\
	PORTE.OUTCLR = 0b00001111; /* set a1 and b1 floating -- important to do this in this order to avoid shoot through!! */ 	\
	PORTE.OUTSET = 0b00000010; /* set a1 low */ \

#define SET_PHASE_STATE_5_MOT1() \
	/* A float, B low, C PWM */ \
								\
	phaseOutputsEHigh &= 0b11000000; \
	phaseOutputsEHigh |= 0b00010000; \
									\
	phaseOutputsELow &= 0b11000000; \
	phaseOutputsELow |= 0b00100000; \
									\
	PORTE.OUTCLR = 0b00001111; /* set b1 and a1 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTE.OUTSET = 0b00001000; /* set b1 low */ \

// Motor 2

#define SET_PHASE_STATE_0_MOT2() \
	phaseOutputsEHigh &= 0b00111111; \
	phaseOutputsEHigh |= 0b01000000;  /* set bits 6-7 of phaseOutputsEHigh to 01 */ \
									\
	phaseOutputsELow &= 0b00111111; \
	phaseOutputsELow |= 0b10000000; /* and 10 for phaseOutputsELow */ \
									\
	phaseOutputsFHigh &= 0b11110000; /* set bits 0-3 of phaseOutputsFHigh and phaseOutputsFLow to 0 */ \
	phaseOutputsFLow &= 0b11110000; \
									\
	PORTF.OUTCLR = 0b00001111; /* set b2 floating -- important to do this in this order to avoid shoot through!! (and set c2 floating)  */ \
	PORTF.OUTSET = 0b00000010; /* set b2 low */

#define SET_PHASE_STATE_1_MOT2() \
	phaseOutputsEHigh &= 0b00111111; \
	phaseOutputsEHigh |= 0b01000000;  /* set bits 6-7 of phaseOutputsEHigh to 01 */ \
									\
	phaseOutputsELow &= 0b00111111; \
	phaseOutputsELow |= 0b10000000; /* and 10 for phaseOutputsELow */ \
									\
	phaseOutputsFHigh &= 0b11110000; /* set bits 0-3 of phaseOutputsFHigh and phaseOutputsFLow to 0 */ \
	phaseOutputsFLow &= 0b11110000; \
									\
	PORTF.OUTCLR = 0b00001111; /* set c2 floating -- important to do this in this order to avoid shoot through!! (and set b2 floating) */ \
	PORTF.OUTSET = 0b00001000; /* set c2 low */
	

#define SET_PHASE_STATE_2_MOT2() \
	phaseOutputsEHigh &= 0b00111111; \
	phaseOutputsELow &= 0b00111111; \
									\
	phaseOutputsFHigh &= 0b11110000; \
	phaseOutputsFHigh |= 0b00000001; \
									\
	phaseOutputsFLow &= 0b11110000; \
	phaseOutputsFLow |= 0b00000010; \
									\
	PORTF.OUTCLR = 0b00001100; /* set c2 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTF.OUTSET = 0b00001000; /* set c2 low */ \
									\
	PORTE.OUTCLR = 0b11000000; /* set a2 floating */

#define SET_PHASE_STATE_3_MOT2() \
	phaseOutputsEHigh &= 0b00111111; \
	phaseOutputsELow &= 0b00111111; \
									\
	phaseOutputsFHigh &= 0b11110000; \
	phaseOutputsFHigh |= 0b00000001; \
									\
	phaseOutputsFLow &= 0b11110000; \
	phaseOutputsFLow |= 0b00000010; \
									\
	PORTE.OUTCLR = 0b11000000; /* set a2 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTE.OUTSET = 0b10000000; /* set a2 low */ \
									\
	PORTF.OUTCLR = 0b00001100; /* set c2 floating */

#define SET_PHASE_STATE_4_MOT2() \
	phaseOutputsEHigh &= 0b00111111; \
	phaseOutputsELow &= 0b00111111; \
									\
	phaseOutputsFHigh &= 0b11110000; \
	phaseOutputsFHigh |= 0b00000100; \
									\
	phaseOutputsFLow &= 0b11110000; \
	phaseOutputsFLow |= 0b00001000; \
									\
	PORTE.OUTCLR = 0b11000000; /* set a2 floating -- important to do this in this order to avoid shoot through!! */ 	\
	PORTE.OUTSET = 0b10000000; /* set a2 low */ \
									\
	PORTF.OUTCLR = 0b00000011; /* set b2 floating */

#define SET_PHASE_STATE_5_MOT2() \
	phaseOutputsEHigh &= 0b00111111; \
	phaseOutputsELow &= 0b00111111; \
									\
	phaseOutputsFHigh &= 0b11110000; \
	phaseOutputsFHigh |= 0b00000100; \
									\
	phaseOutputsFLow &= 0b11110000; \
	phaseOutputsFLow |= 0b00001000; \
									\
	PORTF.OUTCLR = 0b00000011; /* set b2 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTF.OUTSET = 0b00000010; /* set b2 low */ \
									\
	PORTE.OUTCLR = 0b11000000; /* set a2 floating */

// Motor 3

#define SET_PHASE_STATE_0_MOT3() \
	/* A PWM, B low, C float */ \
								\
	phaseOutputsFHigh &= 0b00001111; \
	phaseOutputsFHigh |= 0b00010000; \
									\
	phaseOutputsFLow &= 0b00001111; \
	phaseOutputsFLow |= 0b00100000; \
									\
	phaseOutputsDHigh &= 0b11111100; \
	phaseOutputsDLow &= 0b11111100; \
									\
	PORTF.OUTCLR = 0b11000000; /* set b3 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTF.OUTSET = 0b10000000; /* set b3 low */ \
									\
	PORTD.OUTCLR = 0b00000011; /* set c3 floating */

#define SET_PHASE_STATE_1_MOT3() \
	/* A PWM, B float, C low */ \
								\
	phaseOutputsFHigh &= 0b00001111; \
	phaseOutputsFHigh |= 0b00010000; \
									\
	phaseOutputsFLow &= 0b00001111; \
	phaseOutputsFLow |= 0b00100000; \
									\
	phaseOutputsDHigh &= 0b11111100; \
	phaseOutputsDLow &= 0b11111100; \
									\
	PORTD.OUTCLR = 0b00000011; /* set c3 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTD.OUTSET = 0b00000010; /* set c3 low */ \
									\
	PORTF.OUTCLR = 0b11000000; /* set b3 floating */
	
#define SET_PHASE_STATE_2_MOT3()     \
	/* A float, B PWM, C low */      \
								     \
	phaseOutputsFHigh &= 0b00001111; \
	phaseOutputsFHigh |= 0b01000000; \
									 \
	phaseOutputsFLow &= 0b00001111;  \
	phaseOutputsFLow |= 0b10000000;  \
									 \
	phaseOutputsDHigh &= 0b11111100; \
	phaseOutputsDLow &= 0b11111100;  \
									 \
	PORTD.OUTCLR = 0b00000011; /* set c3 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTD.OUTSET = 0b00000010; /* set c3 low */ \
									\
	PORTF.OUTCLR = 0b00110000; /* set a3 floating */

#define SET_PHASE_STATE_3_MOT3() \
	/* A low, B PWM, C float */ \
								\
	phaseOutputsFHigh &= 0b00001111; \
	phaseOutputsFHigh |= 0b01000000; \
									 \
	phaseOutputsFLow &= 0b00001111;  \
	phaseOutputsFLow |= 0b10000000;  \
									 \
	phaseOutputsDHigh &= 0b11111100; \
	phaseOutputsDLow &= 0b11111100;  \
									\
	PORTF.OUTCLR = 0b00110000; /* set a3 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTF.OUTSET = 0b00100000; /* set a3 low */ \
									\
	PORTD.OUTCLR = 0b00000011; /* set c3 floating */

#define SET_PHASE_STATE_4_MOT3() \
	/* A low, B float, C PWM */ \
								\
	phaseOutputsDHigh &= 0b11111100; \
	phaseOutputsDHigh |= 0b00000001; \
									\
	phaseOutputsDLow &= 0b11111100; \
	phaseOutputsDLow |= 0b00000010; \
									 \
	phaseOutputsFHigh &= 0b00001111; \
	phaseOutputsFLow &= 0b00001111;  \
									\
	PORTF.OUTCLR = 0b11110000; /* set a3 and b3 floating -- important to do this in this order to avoid shoot through!! */ 	\
	PORTF.OUTSET = 0b00100000; /* set a3 low */

#define SET_PHASE_STATE_5_MOT3() \
	/* A float, B low, C PWM */ \
								\
	phaseOutputsDHigh &= 0b11111100; \
	phaseOutputsDHigh |= 0b00000001; \
									\
	phaseOutputsDLow &= 0b11111100; \
	phaseOutputsDLow |= 0b00000010; \
									 \
	phaseOutputsFHigh &= 0b00001111; \
	phaseOutputsFLow &= 0b00001111;  \
									\
	PORTF.OUTCLR = 0b11110000; /* set a3 and b1 floating -- important to do this in this order to avoid shoot through!! */ 	\
	PORTF.OUTSET = 0b10000000; /* set b3 low */


// Motor 4

#define SET_PHASE_STATE_0_MOT4()    \
	/* A PWM, B low, C float */     \
								    \
	phaseOutputsDHigh &= 0b00000011;\
	phaseOutputsDHigh |= 0b00000100;\
									\
	phaseOutputsDLow &= 0b00000011; \
	phaseOutputsDLow |= 0b00001000; \
									\
	PORTD.OUTCLR = 0b11110000; /* set b4 and c4 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTD.OUTSET = 0b00100000; /* set b4 low */

#define SET_PHASE_STATE_1_MOT4()    \
	/* A PWM, B float, C low */     \
								    \
	phaseOutputsDHigh &= 0b00000011;\
	phaseOutputsDHigh |= 0b00000100;\
									\
	phaseOutputsDLow &= 0b00000011; \
	phaseOutputsDLow |= 0b00001000; \
									\
	PORTD.OUTCLR = 0b11110000; /* set c4 and b4 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTD.OUTSET = 0b10000000; /* set c4 low */

#define SET_PHASE_STATE_2_MOT4()     \
	/* A float, B PWM, C low */      \
								     \
	phaseOutputsDHigh &= 0b00000011; \
	phaseOutputsDHigh |= 0b00010000; \
									 \
	phaseOutputsDLow &= 0b00000011;  \
	phaseOutputsDLow |= 0b00100000;  \
									 \
	PORTD.OUTCLR = 0b11001100; /* set a3 and c3 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTD.OUTSET = 0b10000000; /* set c3 low */

#define SET_PHASE_STATE_3_MOT4() \
	/* A low, B PWM, C float */ \
								\
	phaseOutputsDHigh &= 0b00000011; \
	phaseOutputsDHigh |= 0b00010000; \
									 \
	phaseOutputsDLow &= 0b00000011;  \
	phaseOutputsDLow |= 0b00100000;  \
									\
	PORTD.OUTCLR = 0b11001100; /* set a3 and c3 floating -- important to do this in this order to avoid shoot through!! */ \
	PORTD.OUTSET = 0b00001000; /* set a3 low */

#define SET_PHASE_STATE_4_MOT4() \
	/* A low, B float, C PWM */ \
								\
	phaseOutputsDHigh &= 0b00000011; \
	phaseOutputsDHigh |= 0b01000000; \
									\
	phaseOutputsDLow &= 0b00000011; \
	phaseOutputsDLow |= 0b10000010; \
									 \
	PORTD.OUTCLR = 0b00111100; /* set a3 and b3 floating -- important to do this in this order to avoid shoot through!! */ 	\
	PORTD.OUTSET = 0b00001000; /* set a3 low */

#define SET_PHASE_STATE_5_MOT4() \
	/* A float, B low, C PWM */ \
								\
	phaseOutputsDHigh &= 0b00000011; \
	phaseOutputsDHigh |= 0b01000000; \
									\
	phaseOutputsDLow &= 0b00000011; \
	phaseOutputsDLow |= 0b10000000; \
									\
	PORTD.OUTCLR = 0b00111100; /* set a4 and b4 floating -- important to do this in this order to avoid shoot through!! */ 	\
	PORTD.OUTSET = 0b00100000; /* set b4 low */
