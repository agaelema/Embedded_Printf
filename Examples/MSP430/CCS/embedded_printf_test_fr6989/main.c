//******************************************************************************
//	Embedded version of "printf" function
//
//	Based in this link:
//	http://e2e.ti.com/support/development_tools/code_composer_studio/f/81/p/30479/107146
//
//  Updated by: Haroldo Amaral - agaelema@globo.com
//	v0.14 - 22/02/2016
//
//	log:	. test the initial function
//			. add function "sendbyte()"
//			. add function to float number - beta
//			. add scientific notation to double/float - "embedded_ftoa()" function changed
//			. remove old commentecodes
//			. add binary notation (max of 32bits)
//			. transform basic functions to convert numbers in strings (not send)
//			. remove old commented codes
//			. some fixes in functions
//			. remove old commented codes
//			. rename functions and add #defines
//			. fix some bugs
//			. remove some volatile parameters
//			. add #define to enable or not the padding
//			. remove _nop() function of msp430 used during debug
//			. rename some variables
//			. some optimizations
//				remove (comment) the verificarion "(if == 0) in numbers conversion
//			. add #defines to control functions
//			. change to include version
//			. add function to conver string in number (float/double)
//			+ do little changes
//
//******************************************************************************
#include	<msp430.h>

/*
 * currently controling just functions inside the main
 * - need be equal to configuration inside "embedded_printf.h"
 * TODO: defines controlling the configuration of lib...
 */
#define		ENABLE_PAD								// enable padding in functions
#define		ENABLE_FLOAT							// enable print float/double
//#define		PRECISION_FLOAT							// select precision version - use double variable
//#define		ENABLE_EXTRA_DECIMAL_PLACE				// enabled = 9 dp, disabled = 4 dp
#define		ENABLE_BINARY							// enable binary notation

/*
 * Control Test
 */
#define		TEST_FLOAT
#define		TEST_BINARY

/*
 * currently general configurations must be setted inside the "embedded_printf.h"
 */
#include	"embedded_printf.h"


void main(void) {
	WDTCTL = WDTPW + WDTHOLD;							// Para o watchdog timer

	serial_configure();

	PJSEL0 |= BIT4 | BIT5;                    // configure pin for XT1

	// Disable the GPIO power-on default high-impedance mode to activate
	PM5CTL0 &= ~LOCKLPM5;

	// XT1 Setup
	CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
	CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers
	CSCTL4 &= ~LFXTOFF;
	do
	{
		CSCTL5 &= ~LFXTOFFG;                    // Clear XT1 fault flag
		SFRIFG1 &= ~OFIFG;
	}while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
	CSCTL0_H = 0;                             // Lock CS registers


	/* variables to test */
	char *ptr = "Hello world!";
	char *np = 0;
	long i = 5;
	int bs = sizeof(long int) * 8;                           // Bit to shift
	long mi = ((long)1 << (bs - 1)) + 1;             // Maximum negative number

	while (1)
	{
		char buffer_temp[32];
		volatile int return_value = 0;

		return_value = embedded_printf("\r\n");
		embedded_printf("\r\n");
		embedded_printf("\r\n");
		return_value = embedded_printf("##########################################\r\n");
		return_value = embedded_printf("%s\r\n", ptr);
		return_value = embedded_printf("embedded_printf test\r\n");
		embedded_printf("\r\n");

		embedded_printf("\r\n");
		embedded_printf("##########################################\r\n");
		embedded_printf("------------- Basic Functions ------------\r\n");
		embedded_printf("##########################################\r\n");

		embedded_prints("\r\n", 0, 0);
		embedded_prints("------- embedded_ltoa( ) -------\r\n", 0, 0);

		embedded_prints("\r\n", 0, 0);
		embedded_prints("------- signed and unsigned -------\r\n", 0, 0);

		return_value = embedded_ltoa(buffer_temp, 0, DECIMAL, NON_SIGNED, 0, NON_PAD, LOWER_CASE);
		return_value = embedded_prints(buffer_temp, 0, 0);
		return_value = embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 9876, DECIMAL, NON_SIGNED, 0, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, -9876, DECIMAL, SIGNED, 0, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

#ifdef	TEST_BINARY
		embedded_prints("\r\n", 0, 0);
		embedded_prints("------- binary -------\r\n", 0, 0);

		embedded_ltoa(buffer_temp, 0x01, BINARY, NON_SIGNED, 1, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x01, BINARY, NON_SIGNED, 2, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x01, BINARY, NON_SIGNED, 4, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x01, BINARY, NON_SIGNED, 8, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x01, BINARY, NON_SIGNED, 16, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x01, BINARY, NON_SIGNED, 24, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x01, BINARY, NON_SIGNED, 32, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x00, BINARY, NON_SIGNED, 1, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x00, BINARY, NON_SIGNED, 2, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x00, BINARY, NON_SIGNED, 4, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x00, BINARY, NON_SIGNED, 8, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x00, BINARY, NON_SIGNED, 16, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x00, BINARY, NON_SIGNED, 24, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ltoa(buffer_temp, 0x00, BINARY, NON_SIGNED, 32, NON_PAD, LOWER_CASE);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");
#endif

#ifdef	TEST_FLOAT
#ifdef	PRECISION_FLOAT
		embedded_prints("\r\n", 0, 0);
		embedded_prints("------- embedded_ftoa( ) -------\r\n", 0, 0);

		embedded_ftoa(buffer_temp, (double)0.0, 4, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)0.0001, 4, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)-0.0001, 4, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)0.0001, 4, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)-0.0001, 4, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)-1234.5678, 4, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)1234.5678, 4, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)-1234.5678, 2, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)1234.5678, 2, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)9.9979919, 7, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)-9.9979919, 7, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)0, -7, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)-0, -7, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (double)0, 2, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");
		embedded_printf("\r\n");
#else
		embedded_prints("\r\n", 0, 0);
		embedded_prints("------- embedded_ftoa( ) -------\r\n", 0, 0);

		embedded_ftoa(buffer_temp, (float)0.0, 4, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)0.0001, 4, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)-0.0001, 4, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)0.0001, 4, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)-0.0001, 4, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)-1234.5678, 4, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)1234.5678, 4, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)-1234.5678, 2, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)1234.5678, 2, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)9.9979919, 7, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)-9.9979919, 7, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)0, -7, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)-0, -7, SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");

		embedded_ftoa(buffer_temp, (float)0, 2, NON_SCI);
		embedded_prints(buffer_temp, 0, 0);
		embedded_printf("\r\n");
		embedded_printf("\r\n");
#endif
#endif



		return_value = embedded_printf("\r\n");
		embedded_printf("##########################################\r\n");
		embedded_printf("-------- embedded_printf( ) like ---------\r\n");
		embedded_printf("##########################################\r\n");

		embedded_printf("\r\n");
		embedded_printf("------- Signed, Unsigned and Hex -------\r\n");
		embedded_printf("%s is null pointer\r\n", np);
		return_value = embedded_printf("%d = 5\r\n", (long)i);
		embedded_printf("%d = - max int\r\n", mi);
		embedded_printf("Long int 123456789 print out is %u", (long)123456789);
		embedded_printf("\r\nmi in hex is %x\r\n", (long)mi);
		embedded_printf("bs in dec is %u\r\n", (long)bs);
		embedded_printf("char %c = 'a'\r\n", 'a');
		return_value = embedded_printf("hex %x = ff\r\n", (long)0xff);
		embedded_printf("hex %02x = 00\r\n", (long)0);
		embedded_printf("signed %d = unsigned %u = hex %x\r\n", (long)-32767, (long)-32767, (long)-32767);
		embedded_printf("signed %d = unsigned %u = hex %x\r\n", (long)-3, (long)-3, (long)-3);
		embedded_printf("\r\n");



		embedded_printf("------- Multiple arguments -------\r\n");
		embedded_printf("%d %s(s)%", (long)0, "message");
		embedded_printf("\r\n");
		embedded_printf("%d %s(s) with %%\r\n", (long)0, "message");
		embedded_printf("\r\n");

		embedded_printf("------- Justified and Padded -------\r\n");
		embedded_printf("justif: \"%-10s\"\r\n", "left");
		embedded_printf("justif: \"%10s\"\r\n", "right");
		embedded_printf(" 3: %04d zero padded\r\n", (long)3);
		embedded_printf(" 3: %-4d left justif.\r\n", (long)3);
		embedded_printf(" 3: %4d right justif.\r\n", (long)3);
		embedded_printf("-3: %04d zero padded\r\n", (long)-3);
		embedded_printf("-3: %-4d left justif.\r\n", (long)-3);
		embedded_printf("-3: %4d right justif.\r\n", (long)-3);

		embedded_printf("\r\n");
		embedded_printf("%.7d = 5 (float precision not affect integer)\r\n", (long) i);
		embedded_printf("%.4d = - max int (float precision not affect integer)\r\n", mi);
		embedded_printf("\r\n");


#ifdef	TEST_FLOAT

#ifdef 	PRECISION_FLOAT
		embedded_printf("\r\n");
		embedded_printf("------- embedded_printf( ) - float ------\r\n");
		return_value = embedded_printf("%f\r\n", (double)-0);
		return_value = embedded_printf("%f\r\n", (double)9.9898);
		embedded_printf("%f\r\n", (double)-9.9898);
		embedded_printf("%.1f\r\n", (double)9.9898);
		embedded_printf("%.2f\r\n", (double)-9.9898);
		embedded_printf("%.3f\r\n", (double)9.9898);
		return_value = embedded_printf("%.4f\r\n", (double)-9.9898);
		return_value = embedded_printf("%.5f\r\n", (double)9.9898);
		embedded_printf("\r\n");
		embedded_printf("\r\n");
#else
		embedded_printf("\r\n");
		embedded_printf("------- embedded_printf( ) - float ------\r\n");
		return_value = embedded_printf("%f\r\n", (float)-0);
		return_value = embedded_printf("%f\r\n", (float)9.9898);
		embedded_printf("%f\r\n", (float)-9.9898);
		embedded_printf("%.1f\r\n", (float)9.9898);
		embedded_printf("%.2f\r\n", (float)-9.9898);
		embedded_printf("%.3f\r\n", (float)9.9898);
		return_value = embedded_printf("%.4f\r\n", (float)-9.9898);
		return_value = embedded_printf("%.5f\r\n", (float)9.9898);
		embedded_printf("\r\n");
		embedded_printf("\r\n");
#endif


#ifdef 	PRECISION_FLOAT
		embedded_printf("\r\n");
		embedded_printf("##########################################\r\n");
		embedded_printf("#### embedded_printf( ) - scientific #####\r\n");
		embedded_printf("##########################################\r\n");

		embedded_printf("%e\r\n", (double)1.23456789);
		embedded_printf("%e\r\n", (double)-9.69983459);
		embedded_printf("\r\n");

		embedded_printf("%.1e\r\n", (double)-12.3456789);
		embedded_printf("%.2e\r\n", (double)123.456789);
		embedded_printf("%.3e\r\n", (double)-1234.56789);
		embedded_printf("%.4e\r\n", (double)12345.6789);
		embedded_printf("%.5e\r\n", (double)-123456.789);
		embedded_printf("\r\n");
		embedded_printf("%.5e\r\n", (double)0.12345);
		embedded_printf("%.5e\r\n", (double)-0.012345);
		embedded_printf("%.5e\r\n", (double)0.0012345);
		return_value = embedded_printf("%.5e\r\n", (double)-0.00012345);
		return_value = embedded_printf("%.5e\r\n", (double)0.000012345);
		return_value = embedded_printf("%.5e\r\n", (double)-0.0000012345);
		embedded_printf("%.5e\r\n", (double)1.2345e-9);
		return_value = embedded_printf("%.5e\r\n", (double)-1.2345e-9);
		embedded_printf("\r\n");
		embedded_printf("\r\n");
#else
		embedded_printf("\r\n");
		embedded_printf("##########################################\r\n");
		embedded_printf("#### embedded_printf( ) - scientific #####\r\n");
		embedded_printf("##########################################\r\n");

		embedded_printf("%e\r\n", (float)1.23456789);
		embedded_printf("%e\r\n", (float)-9.69983459);
		embedded_printf("\r\n");

		embedded_printf("%.1e\r\n", (float)-12.3456789);
		embedded_printf("%.2e\r\n", (float)123.456789);
		embedded_printf("%.3e\r\n", (float)-1234.56789);
		embedded_printf("%.4e\r\n", (float)12345.6789);
		embedded_printf("%.5e\r\n", (float)-123456.789);
		embedded_printf("\r\n");
		embedded_printf("%.5e\r\n", (float)0.12345);
		embedded_printf("%.5e\r\n", (float)-0.012345);
		embedded_printf("%.5e\r\n", (float)0.0012345);
		return_value = embedded_printf("%.5e\r\n", (float)-0.00012345);
		return_value = embedded_printf("%.5e\r\n", (float)0.000012345);
		return_value = embedded_printf("%.5e\r\n", (float)-0.0000012345);
		embedded_printf("%.5e\r\n", (float)1.2345e-9);
		return_value = embedded_printf("%.5e\r\n", (float)-1.2345e-9);
		embedded_printf("\r\n");
		embedded_printf("\r\n");
#endif

#endif


#ifdef	TEST_BINARY
		embedded_printf("\r\n");
		embedded_printf("------- Binary notation ------\r\n");

		embedded_printf("0x00 = %01b\r\n", (long)0x00);
		embedded_printf("0x01 = %02b\r\n", (long)0x01);
		embedded_printf("0x02 = %04b\r\n", (long)0x02);
		embedded_printf("0x03 = %08b\r\n", (long)0x03);
		embedded_printf("0x04 = %12b\r\n", (long)0x04);
		embedded_printf("0x08 = %16b\r\n", (long)0x08);
		embedded_printf("0x0F = %24b\r\n", (long)0x0F);
		embedded_printf("0xFF = %32b\r\n", (long)0xFF);
		embedded_printf("0xAABBCCDD = %32b\r\n", (long)0xAABBCCDD);
#endif



		print_string("\r\n\r\n");
		print_string("--------Teste Simples Functions-----\r\n");
		print_long(987654321);
		print_string("\r\n");
		print_long(-987654321);
		print_string("\r\n");
		print_ulong(987654321);
		print_string("\r\n");
#ifdef	TEST_BINARY
		print_binary(0xFFFF, 32);
		print_string("\r\n");
#endif
		print_hexa(0xF0F0);
		print_string("\r\n");


#ifdef	TEST_FLOAT

#ifdef 	PRECISION_FLOAT
		print_float((double)1234.5678, 4);
		print_string("\r\n");
		print_float((double)9876.1234, 0);
		print_string("\r\n");
		print_float((double)0.0001, 4);
		print_string("\r\n");
		print_float((double)0.0001, 0);
		print_string("\r\n");
		print_scientific((double)9.9876e19, 4);
		print_string("\r\n");
		print_scientific((double)9.9876e-29, 4);
		print_string("\r\n");
		print_scientific((double)-9.9876e49, 2);
		print_string("\r\n");
		print_scientific((double)-9.9876e-99, 2);
		print_string("\r\n");
#else
		print_float((float)1234.5678, 4);
		print_string("\r\n");
		print_float((float)9876.1234, 0);
		print_string("\r\n");
		print_float((float)0.0001, 4);
		print_string("\r\n");
		print_float((float)0.0001, 0);
		print_string("\r\n");
		print_scientific((float)9.9876e19, 4);
		print_string("\r\n");
		print_scientific((float)9.9876e-29, 4);
		print_string("\r\n");
		print_scientific((float)-9.9876e49, 2);
		print_string("\r\n");
		print_scientific((float)-9.9876e-99, 2);
		print_string("\r\n");
#endif

#endif

		print_string("\r\n");
		print_string("-------- Return test -----\r\n");
		return_value = 0;
		return_value = embedded_printf("%u", (unsigned long)987654321);
		embedded_printf("\r\n- return_value = %u\r\n", (long)return_value);
		return_value = embedded_ltoa(buffer_temp, 987654321, DECIMAL, NON_SIGNED, 0, NON_PAD, LOWER_CASE);
		embedded_printf("\r\n- return_value = %u\r\n", return_value);
		return_value = print_ulong(987654321);
		embedded_printf("\r\n- return_value = %u\r\n", return_value);
		return_value = embedded_prints("987654321", 0, NON_PAD);
		embedded_printf("\r\n- return_value = %u\r\n", return_value);
		return_value = print_string("987654321");
		embedded_printf("\r\n- return_value = %u\r\n", return_value);

#ifdef	TEST_FLOAT
		print_string("\r\n");
		embedded_printf("%.9f\r\n", (double)9.9999999899);
		embedded_printf("%.9f\r\n", (double)-9.9999999899);
		embedded_printf("%.9e\r\n", (double)9.9999999899);
		embedded_printf("%.9e\r\n", (double)-9.9999999899);
#endif

		_nop();
	}
}

////  Echo back RXed character, confirm TX buffer is ready first
//#pragma vector=USCIAB0RX_VECTOR
//__interrupt void USCI0RX_ISR(void) {
//
//	buffer_rx = UCA0RXBUF;								// salva o valor armazenado no buffer de recebimento do MSP430
//	while ((IFG2&UCA0TXIFG) != UCA0TXIFG);				// USCI_A0 TX buffer ready / se o buffer estiver pronto / mesmo que "while(!(IFG2&UCA0TXIFG));"
//
//	UCA0TXBUF = buffer_rx;								// armazena o caracter no buffer de transmissão
//}
