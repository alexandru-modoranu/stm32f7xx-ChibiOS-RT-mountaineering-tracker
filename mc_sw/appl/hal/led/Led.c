/*============================================================================*/
/*                        					                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* $Source: Led.c $
* $Revision: $
* Author: MoMoTech
* $Date: $
*/
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/**
* @file Led.c
* @brief Implements a generic LED driver.
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
#include <string.h>
#include "Led.h"
#include "Vfb.h"
#include "SoftwareTimer.h"

/**@enum Led_ExecStateTypeTag
 * @brief Specifies the possible execution states of a LED execution function (hear beat, toggle etc.).
 */
typedef enum Led_ExecStateTypeTag
{
	LED_EXEC_STATE_INACTIVE = 0u,	/**< Inactive state. */
	LED_EXEC_STATE_ACTIVE,			/**< Active state. */
	LED_EXEC_STATE_UNKNOWN			/**< State can't be determined. Also used as a guard. */
} Led_ExecStateType;

/**@struct Led_ConfigType
 * @brief Generic container for a LED.
 */
typedef struct Led_ConfigTypeTag
{
	void (*exec)(const Led_IdType id);	/**< Pointer to an execution function (heart beat, toggle etc.). */
	uint32_t pinNumber;					/**< Pin number (uC dependent) to which the LED is connected. */
	uint8_t isInverted;					/**< Output value is inverted or not. */
} Led_ConfigType;

/**@struct Led_TimerType
 * @brief Container for the LED activation timer(s).
 */
typedef struct Led_TimerTypeTag
{
	uint32_t activeElapsed;			/**< Number of MainFunction cycles left until the active state is finished. */
	uint32_t activeReload;			/**< Number of MainFunction cycles configured for the active state of the LED. */
	uint8_t activeCyclesElapsed;	/**< Number of MainFunction cycles left until the active state of the execution function is finished. */
	uint8_t activeCyclesReload;		/**< Number of MainFunction cycles configured until the active state of the execution function is finished. */
	uint32_t inactiveElapsed;		/**< Number of MainFunction cycles left until the inactive state is finished. */
	uint32_t inactiveReload;		/**< Number of MainFunction cycles configured for the inactive state of the LED. */
} Led_TimerType;

/**@struct Led_ContainerType
 * @brief Container used to store the relevant data for a LED.
 */
typedef struct Led_ContainerTypeTag
{
	Led_ConfigType config;			/**< Configuration of the LED. */
	Led_TimerType timer;			/**< Timer(s) for the LED. */
	Led_StateType state;			/**< State of the LED. */
	Led_ExecStateType execState;	/**< Execution function state for the LED. */
} Led_ContainerType;

/**@struct Led_DataType
 * @brief Container used to store the relevant data of the LED driver.
 */
typedef struct Led_DataTypeTag
{
	uint32_t mainFunctionRec;						/**< MainFunction recurrence in milliseconds. */
	Led_ContainerType container[LED_ID_UNKNOWN];	/**< Configuration containers for each available LED. */
} Led_DataType;

static void setLedActive(const Led_IdType id);
static void setLedInactive(const Led_IdType id);
static Led_StateType getLedState(const Led_IdType id);
static void toggleLed(const Led_IdType id);

static void toggleExec(const Led_IdType id);
static void heartBeatExec(const Led_IdType id);

/**@brief Stores the LED driver data.
 */
static Led_DataType Led_Data;

/**@brief Used to store the LED HW configuration.
 */
static const Led_ConfigType Led_Config[LED_ID_UNKNOWN] =
{
	{heartBeatExec, LINE_LED_GREEN, FALSE}
};

/**@brief Used to initialize the LED driver.
 * @param[in]	rec	The recurrence of the MainFunction in milliseconds.
 */
void Led_Init(uint32_t rec)
{
	uint32_t id = 0u;

	memset(&Led_Data, 0u, sizeof(Led_Data));
	Led_Data.mainFunctionRec = rec;

	for (id = 0u; id < (uint32_t)LED_ID_UNKNOWN; id++)
	{
		memcpy(&Led_Data.container[id].config, &Led_Config[id], sizeof(Led_Data.container[id].config));
		setLedInactive(id);
		Led_Data.container[id].state = getLedState(id);
		Led_Data.container[id].execState = LED_EXEC_STATE_UNKNOWN;

		if (Led_Data.container[id].config.exec != NULL)
		{
			switch (Led_Data.container[id].state)
			{
			case LED_STATE_OFF:
				Led_Data.container[id].execState = LED_EXEC_STATE_INACTIVE;
				break;
			case LED_STATE_ON:
				Led_Data.container[id].execState = LED_EXEC_STATE_ACTIVE;
				break;
			default:
				Led_Data.container[id].execState = LED_EXEC_STATE_UNKNOWN;
				break;
			}
		}
	}
}

/**@brief Used to execute the LED's assigned function.
 */
void Led_MainFunction(void)
{
	uint32_t id = 0u;

	for (id = 0u; id < LED_ID_UNKNOWN; id++)
	{
		if (Led_Data.container[id].config.exec != NULL)
		{
			Led_Data.container[id].config.exec(id);
		}
	}
}

/**@brief Used to deinitialize the LED driver.
 */
void Led_Deinit(void)
{
	uint32_t id = 0u;

	for (id = 0u; id < (uint32_t)LED_ID_UNKNOWN; id++)
	{
		setLedInactive(id);
		Led_Data.container[id].state = LED_STATE_OFF;
		memset(&Led_Data.container[id].timer, 0u, sizeof(Led_Data.container[id].timer));
	}
}

/**@brief Used to set a LED in the ON state.
 * @param[in]	id	LED identifier.
 */
void Led_SetOn(const Led_IdType id)
{
	setLedActive(id);
}

/**@brief Used to set a LED in the OFF state.
 * @param[in]	id	LED identifier.
 */
void Led_SetOff(const Led_IdType id)
{
	setLedInactive(id);
}

/**@brief LED toggle initializer.
 * @param[in]	id	LED identifier
 * @param[in]	activeTime	Number of milliseconds in which the LED is in the ON state.
 * @param[in]	idleTime	Number of milliseconds in which the LED is in the OFF state.
 */
void Led_Toggle(const Led_IdType id, const uint32_t activeTime, const uint32_t idleTime)
{
	if ((id < LED_ID_UNKNOWN) && (Led_Data.mainFunctionRec != 0u))
	{
		Led_Data.container[id].timer.activeReload = activeTime / Led_Data.mainFunctionRec;
		Led_Data.container[id].timer.activeCyclesReload = 1u;
		Led_Data.container[id].timer.inactiveReload = idleTime / Led_Data.mainFunctionRec;
	}
}

/**@brief LED heart beat initializer.
 * @param[in]	id	LED identifier
 * @param[in]	activeTime	Number of milliseconds in which the LED is in the ON state.
 * @param[in]	activeCycles	Number of ON-OFF cycles to be executed.
 * @param[in]	idleTime	Number of milliseconds in which the LED is in the OFF state.
 */
void Led_HeartBeat(const Led_IdType id, const uint32_t activeTime, const uint8_t activeCycles, const uint32_t idleTime)
{
	if ((id < LED_ID_UNKNOWN) && (Led_Data.mainFunctionRec != 0u))
	{
		Led_Data.container[id].timer.activeReload = activeTime / Led_Data.mainFunctionRec;
		Led_Data.container[id].timer.activeCyclesReload = activeCycles;
		Led_Data.container[id].timer.inactiveReload = idleTime / Led_Data.mainFunctionRec;
	}
}

/**@brief Used to retrieve the internal state of the LED.
 * @param[in]	id	LED identifier
 * @return	LED state.
 */
Led_StateType Led_GetState(const Led_IdType id)
{
	return Led_Data.container[id].state;
}

/**@brief Used to set the output LED in the on state.
 * @param[in]	id	LED identifier
 */
static void setLedActive(const Led_IdType id)
{
	if (id < LED_ID_UNKNOWN)
	{
		if (Led_Data.container[id].config.isInverted)
		{
			Vfb_Write_Port_Line_Value(Led_Data.container[id].config.pinNumber, STD_LOW);
		}
		else
		{
			Vfb_Write_Port_Line_Value(Led_Data.container[id].config.pinNumber, STD_HIGH);
		}
		Led_Data.container[id].state = getLedState(id);
	}
}

/**@brief Used to set the output LED in the off state.
 * @param[in]	id	LED identifier
 */
static void setLedInactive(const Led_IdType id)
{
	if (id < LED_ID_UNKNOWN)
	{
		if (Led_Data.container[id].config.isInverted)
		{
			Vfb_Write_Port_Line_Value(Led_Data.container[id].config.pinNumber, STD_HIGH);
		}
		else
		{
			Vfb_Write_Port_Line_Value(Led_Data.container[id].config.pinNumber, STD_LOW);
		}
		Led_Data.container[id].state = getLedState(id);
	}
}

/**@brief Used to get output LED state.
 * @param[in]	id	LED identifier
 * @return		State of the LED. OFF if turned off, ON if turned on. UNKNOWN if the state can't be determined.
 */
static Led_StateType getLedState(const Led_IdType id)
{
	Led_StateType retVal = LED_STATE_UNKNOWN;
	if (id < LED_ID_UNKNOWN)
	{
		uint8_t tmp;

		if (Led_Config[id].isInverted)
		{
			tmp = ((~Vfb_Read_Port_Line_Value(Led_Data.container[id].config.pinNumber)) & 1u);
		}
		else
		{
			tmp = ((Vfb_Read_Port_Line_Value(Led_Data.container[id].config.pinNumber)) & 1u);
		}
		if (tmp != 0u)
		{
			retVal = LED_STATE_ON;
		}
		else
		{
			retVal = LED_STATE_OFF;
		}
	}

	return retVal;
}

/**@brief Used to toggle the output state of the LED based on the read state of the output pin.
 * @param[in]	id	LED identifier
 */
static void toggleLed(const Led_IdType id)
{
	Vfb_Write_Port_Line_Value(Led_Data.container[id].config.pinNumber, ((~Vfb_Read_Port_Line_Value(Led_Data.container[id].config.pinNumber)) & 1u));
	Led_Data.container[id].state = getLedState(id);
}

/**@brief Implements the toggle LED function.
 * @param[in]	id	LED identifier
 */
static void toggleExec(const Led_IdType id)
{
	switch (Led_Data.container[id].execState)
	{
	case LED_EXEC_STATE_INACTIVE:
		swTimer_tick(Led_Data.container[id].timer.inactiveElapsed);
		if (swTimer_isElapsed(Led_Data.container[id].timer.inactiveElapsed))
		{
			Led_Data.container[id].execState = LED_EXEC_STATE_ACTIVE;
			swTimer_set(Led_Data.container[id].timer.activeElapsed, Led_Data.container[id].timer.activeReload);
			setLedActive(id);
		}
		break;
	case LED_EXEC_STATE_ACTIVE:
		swTimer_tick(Led_Data.container[id].timer.activeElapsed);
		if (swTimer_isElapsed(Led_Data.container[id].timer.activeElapsed))
		{
			Led_Data.container[id].execState = LED_EXEC_STATE_INACTIVE;
			swTimer_set(Led_Data.container[id].timer.inactiveElapsed, Led_Data.container[id].timer.inactiveReload);
			setLedInactive(id);
		}
		break;
	default:
		swTimer_stop(Led_Data.container[id].timer.activeElapsed);
		swTimer_stop(Led_Data.container[id].timer.inactiveElapsed);
		setLedInactive(id);
		break;
	}
}

/**@brief Implements the LED Heart Beat function.
 * @param[in]	id	LED identifier
 */
static void heartBeatExec(const Led_IdType id)
{
	switch (Led_Data.container[id].execState)
	{
	case LED_EXEC_STATE_INACTIVE:
		swTimer_tick(Led_Data.container[id].timer.inactiveElapsed);
		if (swTimer_isElapsed(Led_Data.container[id].timer.inactiveElapsed))
		{
			Led_Data.container[id].execState = LED_EXEC_STATE_ACTIVE;
			swTimer_set(Led_Data.container[id].timer.activeElapsed, Led_Data.container[id].timer.activeReload);
			Led_Data.container[id].timer.activeCyclesElapsed = Led_Data.container[id].timer.activeCyclesReload;
			setLedActive(id);
		}
		break;
	case LED_EXEC_STATE_ACTIVE:
		swTimer_tick(Led_Data.container[id].timer.activeElapsed);
		if (swTimer_isElapsed(Led_Data.container[id].timer.activeElapsed))
		{
			if (Led_Data.container[id].timer.activeCyclesElapsed == 0u)
			{
				Led_Data.container[id].execState = LED_EXEC_STATE_INACTIVE;
				swTimer_set(Led_Data.container[id].timer.inactiveElapsed, Led_Data.container[id].timer.inactiveReload);
				setLedInactive(id);
			}
			else
			{
				swTimer_set(Led_Data.container[id].timer.activeElapsed, Led_Data.container[id].timer.activeReload);
				Led_Data.container[id].timer.activeCyclesElapsed--;
				toggleLed(id);
			}
		}
		break;
	default:
		swTimer_stop(Led_Data.container[id].timer.activeElapsed);
		swTimer_stop(Led_Data.container[id].timer.inactiveElapsed);
		Led_Data.container[id].timer.activeCyclesElapsed = 0u;
		setLedInactive(id);
		break;
	}
}
