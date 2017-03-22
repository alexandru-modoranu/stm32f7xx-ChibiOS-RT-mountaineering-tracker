/*============================================================================*/
/*                        					                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* $Source: Led.h $
* $Revision: $
* Author: MoMoTech
* $Date: $
*/
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/**
* @file Led.h
* @brief Implements the header of the generic LED driver.
*/
/*============================================================================*/
/* MIT License
 *
 * Copyright (c) 2017 MoMo.Tech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.																  */
/*============================================================================*/
#if !defined(LED_H)
#define LED_H

#include "halconf.h"
#include "chtypes.h"
#include "cmparams.h"

/**@enum Led_StateTypeTag
 * @brief Specifies the possible states of the LED.
 */
typedef enum Led_StateTypeTag
{
	LED_STATE_OFF = 0u,	/**< OFF state (no light) of the LED. */
	LED_STATE_ON,		/**< ON state (light) of the LED. */
	LED_STATE_UNKNOWN	/**< State of the LED can't be determined. Also used as a guard. */
} Led_StateType;

/**@enum Led_IdTypeTag
 * @brief Specifies the available HW LEDs.
 */
typedef enum Led_IdTypeTag
{
	LED_ID_USER0 = 0u,	/**< User LED 0. */
	LED_ID_UNKNOWN		/**< Guard value. */
} Led_IdType;

extern void Led_Init(const uint32_t rec);
extern void Led_MainFunction(void);
extern void Led_Deinit(void);
extern void Led_SetOn(const Led_IdType id);
extern void Led_SetOff(const Led_IdType id);
extern void Led_Toggle(const Led_IdType id, const uint32_t activeTime, const uint32_t idleTime);
extern void Led_HeartBeat(const Led_IdType id, const uint32_t activeTime, const uint8_t activeCycles, const uint32_t idleTime);
extern Led_StateType Led_GetState(const Led_IdType id);

#endif /* LED_H */
