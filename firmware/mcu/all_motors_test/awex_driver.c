/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief XMEGA AWeX driver source file.
 *
 *      This file contains the function implementations the XMEGA AWeX driver.
 *
 *      The driver is not intended for size and/or speed critical code, since
 *      most functions are just a few lines of code, and the function call
 *      overhead would decrease code performance. The driver is intended for
 *      rapid prototyping and documentation purposes for getting started with
 *      the XMEGA AWeX module.
 *
 *      For size and/or speed critical code, it is recommended to copy the
 *      function contents directly into your application instead of making
 *      a function call.
 *
 * \par Application note:
 *      AVR1311: Using the XMEGA Timer/Counter Extensions.
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * $Revision: 1569 $
 * $Date: 2008-04-22 13:03:43 +0200 (ti, 22 apr 2008) $  \n
 *
 * Copyright (c) 2008, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include "awex_driver.h"

/*! \brief Enable Dead Time Insertion
 *
 *  This function enables Dead Time Insertion for the channels selected in the
 *  enableMask. The enableMask can be obtained by ORing together the symbols
 *    - AWEX_DTICCAEN_bm
 *    - AWEX_DTICCBEN_bm
 *    - AWEX_DTICCCEN_bm
 *    - AWEX_DTICCDEN_bm
 *
 *  \param awex        The AWEX module.
 *  \param enableMask  Mask of channels to enable.
 */
void AWEX_EnableDeadTimeInsertion( AWEX_t * awex, uint8_t enableMask )
{
	/* Make sure only the DTI enable bits are affected. */
	enableMask &= ( AWEX_DTICCAEN_bm |
	                AWEX_DTICCBEN_bm |
	                AWEX_DTICCCEN_bm |
	                AWEX_DTICCDEN_bm );

	/* Enable DTI for the selected channels. */
	awex->CTRL |= enableMask;
}


/*! \brief Disable Dead Time Insertion
 *
 *  This function disables Dead Time Insertion for the channels selected in the
 *  disableMask. The disableMask can be obtained by ORing together the symbols
 *    - AWEX_DTICCAEN_bm
 *    - AWEX_DTICCBEN_bm
 *    - AWEX_DTICCCEN_bm
 *    - AWEX_DTICCDEN_bm
 *
 *  \param awex         The AWEX module.
 *  \param disableMask  Mask of channels to disable.
 */
void AWEX_DisableDeadTimeInsertion(AWEX_t * awex, uint8_t disableMask)
{
	/* Make sure only the DTI enable bits are affected. */
	disableMask &= ( AWEX_DTICCAEN_bm |
	                 AWEX_DTICCBEN_bm |
	                 AWEX_DTICCCEN_bm |
	                 AWEX_DTICCDEN_bm );

	/* Disable DTI for the selected channels. */
	awex->CTRL &= ~disableMask;
}


/*! \brief This function configures the Fault Detection function for this AWEX.
 *
 *  \param awex         The AWEX module.
 *  \param faultAction  Action to perform on a fault condition.
 *  \param eventMask    Mask of event channels that will trigger a Fault.
 */
void AWEX_ConfigureFaultDetection( AWEX_t * awex,
                                   AWEX_FDACT_t faultAction,
                                   uint8_t eventMask)
{
	awex->FDCTRL = ( awex->FDCTRL & ~AWEX_FDACT_gm ) | faultAction;
	awex->FDEVMASK = eventMask;
}
