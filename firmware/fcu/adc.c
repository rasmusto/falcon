#include "adc_driver.h"

//#include "/usr/lib/avr/include/avr/iox128a3.h"

void init_adc (ADC_t * adc) 
{
    ADC_CalibrationValues_Load (adc);
    ADC_ConvMode_and_Resolution_Config (adc, ADC_ConvMode_Unsigned, ADC_RESOLUTION_8BIT_gc);
    ADC_Prescaler_Config (adc, ADC_PRESCALER_DIV256_gc); // Fadc = 125khz
    ADC_Reference_Config (adc, ADC_REFSEL_INT1V_gc); // vref = 1V 
    
    
    /* Setup channel 0 to have single ended input and 1x gain. */
    ADC_Ch_InputMode_and_Gain_Config (&(adc->CH0),
                                     ADC_CH_INPUTMODE_SINGLEENDED_gc,
                                     ADC_CH_GAIN_1X_gc);

    /* Enable high level sample complete interrupt for channel 0 */
    ADC_Ch_Interrupts_Config (&(adc->CH0), ADC_CH_INTMODE_COMPLETE_gc, ADC_CH_INTLVL_HI_gc);

    PMIC.CTRL |= PMIC_HILVLEN_bm; // Enable low level interrupts
    ADC_Enable (adc); // Enable ADC A with free running mode
    ADC_Wait_32MHz (adc); // Wait until common mode voltage is stable
}
