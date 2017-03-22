/*============================================================================*/
/*                        					                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* $Source: SoftwareTimer.h $
* $Revision: $
* Author: MoMoTech
* $Date: $
*/
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/**
* @file SoftwareTimer.h
* @brief Implements the macros for the software timers handling.
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
#if !defined(SOFTWARE_TIMER_H)
#define SOFTWARE_TIMER_H

/**@brief Macro for setting the value of a software timer. */
#define swTimer_set(tim, val)		((tim) = (val))

/**@brief Macro for stopping a software timer. */
#define swTimer_stop(tim)			((tim) = 0)

/**@brief Macro for ticking (decrementing) a software timer. */
#define swTimer_tick(tim)			if ((tim) > 0){((tim)--);}

/**@brief Macro for checking if a software timer has elapsed (reached 0). */
#define swTimer_isElapsed(tim)		((tim) == 0)

#endif /* SOFTWARE_TIMER_H */
