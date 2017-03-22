/*============================================================================*/
/*                        					                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* $Source: Os_Cfg.c $
* $Revision: $
* Author: MoMoTech
* $Date: $
*/
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/**
* @file Os_Cfg.c
* @brief Implements the OS configuration abstractions.
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
#include "Os_Cfg.h"
#include "Led.h"

/**@brief Defines the wrapper for the thread stack name.
 */
#define THREAD_STACK(thread_name)	(thread_name##_Stack)

/**@brief Defines the wrapper for the OS thread.
 */
#define TASK(tname)					static THD_FUNCTION(tname, arg) { \
										(void)arg; \
										while(TRUE)

/**@brief Defines the wrapper for the OS thred exit condition (thread sleep).
 */
#define TerminateTask()				chThdSleepMilliseconds(currp->recurrence); }

static THD_FUNCTION(Task_2ms, arg);
static THD_FUNCTION(Task_5ms, arg);
static THD_FUNCTION(Task_10ms, arg);
static THD_FUNCTION(Task_20ms, arg);
static THD_FUNCTION(Task_40ms, arg);
static THD_FUNCTION(Task_80ms, arg);
static THD_FUNCTION(Task_100ms, arg);

static THD_WORKING_AREA(THREAD_STACK(Task_2ms), OS_THREAD_STACK_SIZE);
static THD_WORKING_AREA(THREAD_STACK(Task_5ms), OS_THREAD_STACK_SIZE);
static THD_WORKING_AREA(THREAD_STACK(Task_10ms), OS_THREAD_STACK_SIZE);
static THD_WORKING_AREA(THREAD_STACK(Task_20ms), OS_THREAD_STACK_SIZE);
static THD_WORKING_AREA(THREAD_STACK(Task_40ms), OS_THREAD_STACK_SIZE);
static THD_WORKING_AREA(THREAD_STACK(Task_80ms), OS_THREAD_STACK_SIZE);
static THD_WORKING_AREA(THREAD_STACK(Task_100ms), OS_THREAD_STACK_SIZE);

/**@brief Stores the OS wrapper thread configuration.
 */
const OsCfg_ConfigType OsCfg_Config[OS_THREAD_NUMBER] =
{
	{	Task_2ms,	NULL,	NORMALPRIO + 70u,	1u,	2u, 	THD_WORKING_AREA_BASE(THREAD_STACK(Task_2ms)),		THD_WORKING_AREA_END(THREAD_STACK(Task_2ms))  },
	{	Task_5ms,	NULL,	NORMALPRIO + 60u,	2u,	5u, 	THD_WORKING_AREA_BASE(THREAD_STACK(Task_5ms)),		THD_WORKING_AREA_END(THREAD_STACK(Task_5ms))  },
	{	Task_10ms,	NULL,	NORMALPRIO + 50u,	3u,	10u,	THD_WORKING_AREA_BASE(THREAD_STACK(Task_10ms)),		THD_WORKING_AREA_END(THREAD_STACK(Task_10ms)) },
	{	Task_20ms,	NULL,	NORMALPRIO + 40u,	4u,	20u,	THD_WORKING_AREA_BASE(THREAD_STACK(Task_20ms)),		THD_WORKING_AREA_END(THREAD_STACK(Task_20ms)) },
	{	Task_40ms,	NULL,	NORMALPRIO + 30u, 	5u,	40u,	THD_WORKING_AREA_BASE(THREAD_STACK(Task_40ms)),		THD_WORKING_AREA_END(THREAD_STACK(Task_40ms)) },
	{	Task_80ms,	NULL,	NORMALPRIO + 20u,	6u,	80u,	THD_WORKING_AREA_BASE(THREAD_STACK(Task_80ms)),		THD_WORKING_AREA_END(THREAD_STACK(Task_80ms)) },
	{	Task_100ms,	NULL,	NORMALPRIO + 10u,	7u,	100u,	THD_WORKING_AREA_BASE(THREAD_STACK(Task_100ms)),	THD_WORKING_AREA_END(THREAD_STACK(Task_100ms))}
};

/**@brief 2 milliseconds recurrence thread.
 */
TASK(Task_2ms)
{

	TerminateTask();
}

/**@brief 5 milliseconds recurrence thread.
 */
TASK(Task_5ms)
{
	TerminateTask();
}

/**@brief 10 milliseconds recurrence thread.
 */
TASK(Task_10ms)
{
	Led_MainFunction();
	TerminateTask();
}

/**@brief 20 milliseconds recurrence thread.
 */
TASK(Task_20ms)
{
	TerminateTask();
}

/**@brief 40 milliseconds recurrence thread.
 */
TASK(Task_40ms)
{
	TerminateTask();
}

/**@brief 80 milliseconds recurrence thread.
 */
TASK(Task_80ms)
{
	TerminateTask();
}

/**@brief 100 milliseconds recurrence thread.
 */
TASK(Task_100ms)
{
	TerminateTask();
}
