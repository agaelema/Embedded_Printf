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

#include "serial_conf.h"

#ifdef		MSP430
#include	<msp430.h>

#ifdef		G2553
/*
 * Handle the serial code to transmit one byte
 * Each microcontroler has a specific code
 * Input:	char	byte (byte to be transmited)
 * Output:	none
 */
void sendbyte(char byte)
{
#ifdef	USCI_UCA0
	while (!(IFG2 & UCA0TXIFG));    // USCI_A0 TX buffer ready?
	UCA0TXBUF = byte;                                    // Load Tx register that clear UCA0TXIFG
#endif

}
#endif

//#endif
#endif
