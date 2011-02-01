/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief  XMEGA AWeX driver header file.
 *
 *      This file contains the function prototypes and enumerator definitions
 *      for various configuration parameters for the XMEGA AWeX driver.
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

#ifndef __AWEX_DRIVER_H__
#define __AWEX_DRIVER_H__

#include "avr_compiler.h"

/* Definition of macros */

/*! \brief  This macro enables the Common Waveform Channel mode.
 *
 *  \param _awex The AWEX module.
 */
#define AWEX_EnableCommonWaveformChannelMode( _awex ) \
                                            ( _awex->CTRL |= AWEX_CWCM_bm )

/*! \brief This macro disables the Common Waveform Channel mode.
 *
 *  \param _awex The AWEX module.
 */
#define AWEX_DisableCommonWaveformChannelMode( _awex ) \
                                             ( _awex->CTRL &= ~AWEX_CWCM_bm )

/*! \brief This macro enables the Pattern Generation Mode.
 *
 *  \param _awex The AWEX module.
 */
#define AWEX_EnablePatternGenerationMode( _awex ) \
                                             ( _awex->CTRL |= AWEX_PGM_bm )

/*! \brief This macro disables the Pattern Generation Mode.
 *
 *  \param _awex The AWEX module.
 */
#define AWEX_DisablePatternGenerationMode( _awex ) \
                                             ( _awex->CTRL &= ~AWEX_PGM_bm )

/*! \brief This macro sets an output override value.
 *
 *  \param _awex           The AWEX module.
 *  \param _overrideValue  The override value to output.
 */
#define AWEX_SetOutputOverrideValue( _awex, _overrideValue ) \
                                             ( _awex.OUTOVEN = _overrideValue )

/*! \brief This macro returns the status of the Fault Detection.
 *
 *  \param _awex The AWEX module.
 *
 *  \return     The Fault Detection status.
 */
#define AWEX_IsFaultDetected( _awex )        ( _awex->STATUS & AWEX_FDF_bm )

/*! \brief This macro clears the Fault Detected Flag.
 *
 *  Clearing this flag will not undo the Fault Detect action, only clear the
 *  flag.
 *
 *  \param _awex The AWEX module.
 */
#define AWEX_ClearFaultFlag( _awex )          ( _awex->STATUS = AWEX_FDF_bm )

/*! \brief This macro returns the state of the High Side Dead Time Buffer.
 *
 *  \param _awex The AWEX module.
 *
 *  \return     Non-zero if the state of the High Side Dead Time Buffer, zero
 *              otherwise.
 */
#define AWEX_IsDeadTimeBufferHighSideValid( _awex ) \
                                          (  _awex->STATUS & AWEX_DTHSBUFV_bm )

/*! \brief This macro returns the state of the Low Side Dead Time Buffer.
 *
 *  \param _awex The AWEX module.
 *
 *  \return Non-zero if the state of the Low Side Dead Time Buffer, zero
 *          otherwise.
 */
#define AWEX_DeadTimeBufferLowSideValid( _awex ) \
                                  ( _awex->STATUS & AWEX_DTLSBUFV_bm )

/*! \brief This macro sets an equal dead time for high and low side.
 *
 *  When using this macro, the dead time is updated immediately.
 *
 *  \param _awex      The AWEX module.
 *  \param _deadTime  The dead time.
*/
#define AWEX_SetDeadTimesSymmetricalUnbuffered( _awex, _deadTime ) \
                                   ( _awex.DTBOTH = _deadTime )

/*! \brief This macro sets the dead time for high and low side.
 *
 *  When using this macro, the dead times are updated immediately.
 *
 *  \param _awex          The AWEX module.
 *  \param _deadTimeLow   The dead time for low side.
 *  \param _deadTimeHigh  The dead time for high side.
 */
#define AWEX_SetDeadTimeAsymmetricalUnbuffered( _awex, _deadTimeLow, _deadTimeHigh ) \
                        ( _awex->DTLS = _deadTimeLow; \
                          _awex->DTHS = _deadTimeHigh )

/*! \brief This macro sets an equal dead time for high and low side.
 *
 *  When using this macro, the dead time is updated on the next UPDATE
 *  condition.
 *
 *  \param _awex      The AWEX module.
 *  \param _deadTime  The dead time.
 */
#define AWEX_SetDeadTimesSymmetricalBuffered( _awex, _deadTime ) \
                                   ( _awex->DTBOTHBUF = _deadTime )

/*! \brief This macro sets the dead time for high and low side.
 *
 *  When using this macro, the dead times are updated on the next UPDATE
 *  condition.
 *
 *  \param _awex          The AWEX module.
 *  \param _deadTimeLow   The dead time for low side.
 *  \param _deadTimeHigh  The dead time for high side.
 */
#define AWEX_SetDeadTimeAsymmetricalBuffered( _awex, _deadTimeLow, _deadTimeHigh ) \
                       ( _awex->DTLSBUF = _deadTimeLow; \
                         _awex->DTHSBUF = _deadTimeHigh )


/* Prototyping of functions. */

void AWEX_EnableDeadTimeInsertion( AWEX_t * awex,
                                   uint8_t enableMask );
void AWEX_DisableDeadTimeInsertion( AWEX_t * awex,
                                    uint8_t disableMask );
void AWEX_ConfigureFaultDetection( AWEX_t * awex,
                                   AWEX_FDACT_t faultAction,
                                   uint8_t eventMask );

#endif
