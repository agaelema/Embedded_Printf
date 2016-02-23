/*
 *	Embedded version of "printf" function - serial configuration
 *
 *	Based in this link:
 *	http://e2e.ti.com/support/development_tools/code_composer_studio/f/81/p/30479/107146
 *
 *	Updated by: Haroldo Amaral - agaelema@globo.com
 *	Include v 0.1
 *	21/12/2015
 */

#ifndef		SERIAL_CONF
#define		SERIAL_CONF

/*
 *	list of suported Microcontrollers and their serial com
 *	- uncomment desired uC, Model and serial com
 */
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
