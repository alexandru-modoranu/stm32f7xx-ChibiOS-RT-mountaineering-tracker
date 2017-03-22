/*============================================================================*/
/*                        					                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* $Source: Os_Cfg.h $
* $Revision: $
* Author: MoMoTech
* $Date: $
*/
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/**
* @file Os_Cfg.h
* @brief Implements the header of the OS configuration abstractions.
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
#if !defined(OS_CFG_H)
#define OS_CFG_H

#include "ch.h"

/**@brief Defines the maximum number of OS threads.
 */
#define OS_THREAD_NUMBER				(7u)

/**@brief Defines the stack size for each configured OS thread.
 */
#define OS_THREAD_STACK_SIZE			(512u)

/**@struct OsCfg_ConfigType
 * @brief Specifies the configuration container for an OS thread.
 */
typedef struct OsCfg_ConfigTypeTag
{
	tfunc_t pfTaskFunction;			/**< Pointer to thread function. */
	void *pvArguments;				/**< List of arguments to pass to the OS thread. */
	tprio_t ulPriority;				/**< Thread priority. */
	systime_t ulOffset;				/**< Thread activation offset in OS ticks. */
	systime_t ulRecurrence;			/**< Thread activation cycle in OS ticks. */
	stkalign_t *pvTaskStackStart;	/**< Thread stack start address. */
	stkalign_t *pvTaskStackEnd;		/**< Thread stack end address.*/
} OsCfg_ConfigType;

extern const OsCfg_ConfigType OsCfg_Config[OS_THREAD_NUMBER];

#endif /* OS_CFG_H */
