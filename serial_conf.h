/*
 *		uncomment desired uC, Model and serial com
 */

#ifndef		SERIAL_CONF
#define		SERIAL_CONF

// list of suported Microcontrollers and their serial com
#define		MSP430G2553_USCI_A0			1

/*
 * Suported uC
 * If you add a new device, do a pull request and help other users
 */

#if	MSP430G2553_USCI_A0 == 1
#define 	MSP430
#define		G2553
#define		USCI_UCA0
#endif

/*
 * Prototipes
 */
void sendbyte(char byte);

#endif
