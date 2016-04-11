//******************************************************************************
//	"serial_conf.h" used in the embedded version of "printf" function
//
//  author: Haroldo Amaral - agaelema@globo.com
//	v0.2 - 09/04/2016
//
//	log:	. Modify initial version
//			+ more defines to facilitate the configuration between devices
//			+ change function "sendbyte" to "serial_sendbyte"
//			+ add function to configure UART
//
//******************************************************************************

#ifndef		SERIAL_CONF
#define		SERIAL_CONF

// list of suported Microcontrollers and their serial com
#define		MSP430FR6989_USCI_A0			// P2.0 and P2.1
//#define		MSP430G2553_USCI_A0					// P1.1 and P1.2

// list of baudrate
#define		BAUD_9600
//#define		BAUD_115200					// not working

/*
 * Suported microcontrollers
 * If you add a new device, do a pull request and help other users
 */

#ifdef	MSP430FR6989_USCI_A0
#define 	MSP430
#define		FR6989
#define		USCI_UCA0
#endif

#ifdef	MSP430G2553_USCI_A0
#define 	MSP430
#define		G2553
#define		USCI_UCA0
#endif


/*
 * Prototipe of functions
 */
void serial_configure(void);
void serial_sendbyte(char byte);

#endif
