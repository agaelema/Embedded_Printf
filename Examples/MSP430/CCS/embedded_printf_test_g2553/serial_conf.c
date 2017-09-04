//******************************************************************************
//	"serial_conf.c" used in the embedded version of "printf" function
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

#include "serial_conf.h"


/*
 * specific "include" to each device
 */
#ifdef		MSP430					// msp430 header
#include	<msp430.h>
#endif


/*
 * handle serial configuration for each device
 * Input:	none
 * Output:	none
  */
void serial_configure(void)
{
#ifdef	MSP430			// start of MSP430's definitions

#ifdef		FR6989			// start of G2553 definitions
#ifdef		USCI_UCA0
#ifdef		BAUD_9600
	// Configure GPIO
	P2SEL0 |= BIT0 | BIT1;                    // USCI_A0 UART operation
	P2SEL1 &= ~(BIT0 | BIT1);

//	PJSEL0 |= BIT4 | BIT5;                    // For XT1
//
//	// Disable the GPIO power-on default high-impedance mode to activate
//	// previously configured port settings
//	PM5CTL0 &= ~LOCKLPM5;
//
//	// XT1 Setup
//	CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
//	CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
//	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers
//	CSCTL4 &= ~LFXTOFF;
//	do
//	{
//		CSCTL5 &= ~LFXTOFFG;                    // Clear XT1 fault flag
//		SFRIFG1 &= ~OFIFG;
//	}while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
//	CSCTL0_H = 0;                             // Lock CS registers

	// Configure USCI_A0 for UART mode
	UCA0CTLW0 = UCSWRST;                      // Put eUSCI in reset
	UCA0CTLW0 |= UCSSEL__ACLK;                // CLK = ACLK
	UCA0BR0 = 3;                              // 9600 baud
	UCA0MCTLW |= 0x5300;                      // 32768/9600 - INT(32768/9600)=0.41
	// UCBRSx value = 0x53 (See UG)
	UCA0BR1 = 0;
	UCA0CTL1 &= ~UCSWRST;                     // Initialize eUSCI
//	UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
#endif
#ifdef		BAUD_115200
//	  P2SEL0 |= BIT0 | BIT1;                    // USCI_A0 UART operation
//	  P2SEL1 &= ~(BIT0 | BIT1);
//
//	  // Disable the GPIO power-on default high-impedance mode to activate
//	  // previously configured port settings
//	  PM5CTL0 &= ~LOCKLPM5;
//
//	  // Configure USCI_A0 for UART mode
//	  UCA0CTLW0 = UCSWRST;                      // Put eUSCI in reset
//	  UCA0CTL1 |= UCSSEL__SMCLK;                // CLK = SMCLK
//	  UCA0BR0 = 8;                              // 1000000/115200 = 8.68
//	  UCA0MCTLW = 0xD600;                       // 1000000/115200 - INT(1000000/115200)=0.68
//	                                            // UCBRSx value = 0xD6 (See UG)
//	  UCA0BR1 = 0;
//	  UCA0CTL1 &= ~UCSWRST;                     // release from reset
////	  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
#endif
#endif
#endif						// end of G2553 definitions


#ifdef		G2553			// start of G2553 definitions
#ifdef		USCI_UCA0
#ifdef		BAUD_9600
	P1SEL = BIT1 + BIT2;			// P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2;			// P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2;			// fonte de clock para a UART - SMCLK
	UCA0BR0 = 104;					// UCA0BR0 = clock/baud = 1MHz/9600
	UCA0BR1 = 0;					// UCA0BR0 = clock/baud = 1MHz/9600

	UCA0MCTL = UCBRS0;				// Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;			// software reset - Initialize USCI state machine

//	IE2 |= UCA0RXIE;				// Habilita o USCI_A0 RX interrupt
#endif
#endif
#endif						// end of G2553 definitions

#endif						// end of MSP430's definitions
}


/*
 * Handle the serial code to transmit one byte
 * Each microcontroler has a specific code
 * Input:	char	byte (byte to be transmited)
 * Output:	none
 */
void serial_sendbyte(char byte)
{
#ifdef	MSP430			// start of MSP430's definitions

#ifdef	G2553			// start of G2553 definitions
#ifdef		USCI_UCA0
//	while (!(IFG2 & UCA0TXIFG));    // USCI_A0 TX buffer ready? - not using interruption
    while (!(IFG2 & UCA0TXIFG));    // USCI_A0 TX buffer ready? - not using interruption
	UCA0TXBUF = byte;               // Load Tx register that clear UCA0TXIFG
#endif
#endif						// end of G2553 definitions

#ifdef	FR6989			// start of G2553 definitions
#ifdef		USCI_UCA0
	while (!(UCA0IFG & UCTXIFG));    // USCI_A0 TX buffer ready? - not using interruption
	UCA0TXBUF = byte;               // Load Tx register that clear UCA0TXIFG
#endif
#endif						// end of G2553 definitions


#endif						// end of MSP430's definitions
}
