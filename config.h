/****************************************************************************
 * Copyright (C) 2016 by Harald W. Leschner (DK6YF)                         *
 *                                                                          *
 * This file is part of ALPINE M-BUS Interface Control Emulator             *
 *                                                                          *
 * This program is free software you can redistribute it and/or modify		*
 * it under the terms of the GNU General Public License as published by 	*
 * the Free Software Foundation either version 2 of the License, or 		*
 * (at your option) any later version. 										*
 *  																		*
 * This program is distributed in the hope that it will be useful, 			*
 * but WITHOUT ANY WARRANTY without even the implied warranty of 			*
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 			*
 * GNU General Public License for more details. 							*
 *  																		*
 * You should have received a copy of the GNU General Public License 		*
 * along with this program if not, write to the Free Software 				*
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA*
 ****************************************************************************/

/**
 * @file mbus.h
 *
 * @author Harald W. Leschner (DK6YF)
 * @date 23.08.2016
 *
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */




#ifndef CONFIGURE_H_
#define CONFIGURE_H_

#define F_CPU		16000000UL    	/*!< Crystal frequency in Hz */
#define XTAL		F_CPU

#define BAUDRATE 	115200



/******************************************************************
* Module switches, to make code smaller if features are not needed
*******************************************************************/
/*!< BASIC TIMING AND COMMUNICATION */
#define TIME_AVAILABLE			/*!< Is there a system time in s and ms? */
#define DISPLAY_AVAILABLE		/*!< Display for local control and debugging */
//#define WELCOME_AVAILABLE		/*!< Show company welcome message */	
#define UART_AVAILABLE			/*!< Serial Communication */

/*!< LOGGING AUSGANG - nur 1 gleichzeitig moeglich */
//#define LOG_CTSIM_AVAILABLE		/*!< Logging zum ct-Sim (PC und MCU) */
//#define LOG_DISPLAY_AVAILABLE		/*!< Logging ueber das LCD-Display (PC und MCU) */
#define LOG_UART_AVAILABLE			/*!< Logging ueber UART (NUR fuer MCU) */
//#define LOG_STDOUT_AVAILABLE 		/*!< Logging auf die Konsole (NUR fuer PC) */
//#define USE_MINILOG				/*!< schaltet fuer MCU auf schlankes Logging um (nur in Verbindung mit Log2Sim) */



//#define I2C_AVAILABLE				/*!< TWI-Schnittstelle (I2C) nutzen */
//#define SPI_AVAILABLE				/*!< SPI Schnittstelle aktivieren? */

/************************************************************
* Some Dependencies!!!
************************************************************/

#ifndef DISPLAY_AVAILABLE
	#undef WELCOME_AVAILABLE
#endif


#ifdef LOG_UART_AVAILABLE
	#define LOG_AVAILABLE	/*!< LOG aktiv? */
#endif
#ifdef LOG_CTSIM_AVAILABLE
	#define LOG_AVAILABLE	/*!< LOG aktiv? */
#endif
#ifdef LOG_DISPLAY_AVAILABLE
	#define LOG_AVAILABLE	/*!< LOG aktiv? */
#endif
#ifdef LOG_STDOUT_AVAILABLE
	#define LOG_AVAILABLE	/*!< LOG aktiv? */
#endif


#ifdef LOG_AVAILABLE
	#ifndef LOG_CTSIM_AVAILABLE
		#undef USE_MINILOG
	#endif


	/* Mit Bot zu PC Kommunikation auf dem MCU gibts kein Logging ueber UART.
	 * Ohne gibts keine Kommunikation ueber ct-Sim.
	 */
	#undef LOG_STDOUT_AVAILABLE		/*!< MCU hat kein STDOUT */
	#ifdef BOT_2_PC_AVAILABLE
		#undef LOG_UART_AVAILABLE
	#else
		#undef LOG_CTSIM_AVAILABLE
	#endif


	/* Ohne Display gibts auch keine Ausgaben auf diesem. */
	#ifndef DISPLAY_AVAILABLE
		#undef LOG_DISPLAY_AVAILABLE
	#endif

	/* Es kann immer nur ueber eine Schnittstelle geloggt werden. */

	#ifdef LOG_UART_AVAILABLE
		#define UART_AVAILABLE			/*!< UART vorhanden? */
		#undef LOG_CTSIM_AVAILABLE
		#undef LOG_DISPLAY_AVAILABLE
		#undef LOG_STDOUT_AVAILABLE
	#endif

	#ifdef LOG_CTSIM_AVAILABLE
		#undef LOG_DISPLAY_AVAILABLE
		#undef LOG_STDOUT_AVAILABLE
	#endif

	#ifdef LOG_DISPLAY_AVAILABLE
		#undef LOG_STDOUT_AVAILABLE
	#endif

	// Wenn keine sinnvolle Log-Option mehr uebrig, loggen wir auch nicht
	#ifndef LOG_CTSIM_AVAILABLE
		#ifndef LOG_DISPLAY_AVAILABLE
			#ifndef LOG_UART_AVAILABLE
				#ifndef LOG_STDOUT_AVAILABLE
					#undef LOG_AVAILABLE
				#endif
			#endif
		#endif
	#endif

#endif



#include "global.h"




#endif /* CONFIGURE_H_ */
