/* =================================================================================
File name:       SVGEN_MF.H  (IQ version)                   
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the SVGEN_MF.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                               
------------------------------------------------------------------------------*/
#ifndef __SVGEN_MF_H__
#define __SVGEN_MF_H__

typedef struct 	{ _iq  Gain; 				// Input: reference gain voltage (pu) 
				  _iq  Offset;				// Input: reference offset voltage (pu)
				  _iq  Freq;				// Input: reference frequency (pu)
                  _iq  FreqMax;  			// Parameter: Maximum step angle = 6*base_freq*T (pu)
                  _iq  Alpha;     			// History: Sector angle (pu)
                  _iq  NewEntry;    		// History: Sine (angular) look-up pointer (pu)
                  Uint32  SectorPointer;   	// History: Sector number (Q0) - independently with global Q
				  _iq  Ta;					// Output: reference phase-a switching function (pu)		
				  _iq  Tb;					// Output: reference phase-b switching function (pu)
				  _iq  Tc;					// Output: reference phase-c switching function (pu)
				  void   (*calc)();	    	// Pointer to calculation function
				} SVGENMF;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
typedef SVGENMF *SVGENMF_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SVGENMF object.
-----------------------------------------------------------------------------*/                     
#define SVGENMF_DEFAULTS { 0,0,0,0,0,0,0,0,0,0, \
                       (void (*)(Uint32))svgenmf_calc }

#define	PI_THIRD	_IQ(1.04719755119660)    // This is 60 degree
/*------------------------------------------------------------------------------
Prototypes for the functions in SVGEN_MF.C
------------------------------------------------------------------------------*/
void svgenmf_calc(SVGENMF_handle);

#endif // __SVGEN_MF_H__

