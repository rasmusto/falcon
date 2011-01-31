/* =================================================================================
File name:       VHZ_PROF.H  (IQ version)                   
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the VHZPROF.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                
------------------------------------------------------------------------------*/
#ifndef __VHZ_PROF_H__
#define __VHZ_PROF_H__

typedef struct 	{ _iq  Freq; 		    // Input: Input Frequency (pu)
				  _iq  VoltOut;		    // Output: Output voltage (pu)
				  _iq  LowFreq;			// Parameter: Low Frequency (pu)			
				  _iq  HighFreq;		// Parameter: High Frequency at rated voltage (pu)
				  _iq  FreqMax; 		// Parameter: Maximum Frequency (pu)
				  _iq  VoltMax;			// Parameter: Rated voltage (pu)					  
			      _iq  VoltMin;	 		// Parameter: Voltage at low Frequency range (pu)
		  	  	  void  (*calc)();	    // Pointer to calculation function
				} VHZPROF;	                   

typedef VHZPROF *VHZPROF_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the VHZPROF object.
-----------------------------------------------------------------------------*/                     
#define VHZPROF_DEFAULTS { 0,0, \
                           0,0,0,0,0, \
                  		   (void (*)(Uint32))vhz_prof_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in VHZ_PROF.C
------------------------------------------------------------------------------*/
void vhz_prof_calc(VHZPROF_handle);

#endif // __VHZ_PROF_H__
