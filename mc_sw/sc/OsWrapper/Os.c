/*============================================================================*/
/*                        					                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* $Source: Os.c $
* $Revision: $
* Author: MoMoTech
* $Date: $
*/
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/**
* @file Os.c
* @brief Implements the wrapper functions for the OS abstraction.
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
#include "Os.h"

/**@brief Stores the entire thred pool of the OS. */
static thread_t *OsCfg_TaskPool[OS_THREAD_NUMBER];

/**@brief Initialization function of the OS wrapper. */
void Os_Init(void)
{
	uint32_t id = 0u;

	chSysInit();

	for (id = 0u; id < OS_THREAD_NUMBER; id ++)
	{
		/* Initialize the thread descriptor. */
		thread_descriptor_t tdp = {NULL,
								   OsCfg_Config[id].pvTaskStackStart,
								   OsCfg_Config[id].pvTaskStackEnd,
								   OsCfg_Config[id].ulPriority,
								   OsCfg_Config[id].pfTaskFunction,
								   OsCfg_Config[id].pvArguments};
		/* Create a thread and set its state to suspended. */
		OsCfg_TaskPool[id] = chThdCreateSuspended(&tdp);
		/* Assign the thread's first activation offset. */
		OsCfg_TaskPool[id]->startoffset = OsCfg_Config[id].ulOffset;
		/* Assign the thread's cycle time (recurrence in OS ticks). */
		OsCfg_TaskPool[id]->recurrence = OsCfg_Config[id].ulRecurrence;
	}
}

/**@brief OS wrapper function used to start all of the configured OS threads. */
void Os_StartTasks(void)
{
	const systime_t startTime = chVTGetSystemTime();	/* Get the current system time. */
	uint32_t noOfStartedTasks = 0u;						/* Initialize the number of started threads counter. */

	/* Start all of the configured threads. */
	while (noOfStartedTasks <= OS_THREAD_NUMBER)
	{
		uint32_t id = 0u;
		for (id = 0u; id < OS_THREAD_NUMBER; id++)
		{
			/* Check the activation offset for each thread against the system time.
			 * Only check the threads that are suspended. */
			if (!chVTIsSystemTimeWithin(startTime, (startTime + OsCfg_TaskPool[id]->startoffset))
			&& (OsCfg_TaskPool[id]->state == CH_STATE_WTSTART))
			{
				/* Start the thread. */
				chThdStart(OsCfg_TaskPool[id]);

				/* Increment the threads counter. */
				noOfStartedTasks++;

				/* Lock the system.
				 * Request a reschedule point.
				 * Unlock the system. */
				chSysLock();
				chSchRescheduleS();
				chSysUnlock();
			}
		}
	}
}

