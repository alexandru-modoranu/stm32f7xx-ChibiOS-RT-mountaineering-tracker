/*============================================================================*/
/*                        					                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* $Source: Vfb_Port.h $
* $Revision: $
* Author: MoMoTech
* $Date: $
*/
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/**
* @file Vfb_Port.h
* @brief Implements the virtual function bus Port abstraction.
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
#if !defined(VFB_PORT_H)
#define VFB_PORT_H

#include "hal.h"

/**@brief Defines the LOW logic level.
 */
#define STD_LOW		(0u)

/**@brief Defines the HIGH logic level.
 */
#define STD_HIGH	(1u)

/**@brief Defines the virtual function bus macro used to set the mode of a HW pin.
 * @param[in]	line	Pin identifier
 * @param[in]	mode	Pin function
 */
#define Vfb_Write_Port_Line_Mode(line, mode)		palSetLineMode(line, mode)

/**@brief Defines the virtual function bus macro used to set the logic value of a HW pin.
 * @param[in]	line	Pin identifier
 * @param[in]	value	Pin logic value
 */
#define Vfb_Write_Port_Line_Value(line, value)		palWriteLine(line, value)

/**@brief Defines the virtual function bus macro used to get the logic value of a HW pin.
 * @param[in]	line	Pin identifier
 * @return Logic level value of the requested pin.
 */
#define Vfb_Read_Port_Line_Value(line)				palReadLine(line)


#endif /* VFB_PORT_H */
