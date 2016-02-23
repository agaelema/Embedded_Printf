/*
 *	Include v 0.2
 *	21/12/2015
 */

#ifndef		EMBEDDED_PRINTF
#define		EMBEDDED_PRINTF


#define		ENABLE_PAD								// enable padding in functions
#define		ENABLE_FLOAT							// enable print float/double
//#define		PRECISION_FLOAT							// select precision version - use double variable
//#define		ENABLE_EXTRA_DECIMAL_PLACE				// enabled = 9 dp, disabled = 4 dp - depends of PRECISION_FLOAT
#define		ENABLE_BINARY							// enable binary notation



/*
 * PROTOTYPE OF FUNCTIONS
 */
//void sendbyte(char byte);

void putChar(unsigned char byte);

void linesUp(unsigned char lines);

int embedded_prints(char *string, unsigned int width, unsigned int pad);
int embedded_ltoa(char *print_buf, signed long input, unsigned int base, unsigned int sg, unsigned int width, unsigned int pad, unsigned char letbase);


#ifdef	ENABLE_PAD
#define	ENABLE_PAD_
#endif

#ifdef	ENABLE_EXTRA_DECIMAL_PLACE
#define	ENABLE_EXTRA_DECIMAL_PLACE_
#endif

#ifdef ENABLE_FLOAT

#ifdef PRECISION_FLOAT
#define PRECISION_FLOAT_
int embedded_ftoa(char *print_buf, double input, signed int dp, unsigned int sci);
#else
int embedded_ftoa(char *print_buf, float input, signed int dp, unsigned int sci);
#endif
#endif

int embedded_printf(char *format, ...);

unsigned int print_string(char *string);
unsigned int print_long(long number);
unsigned int print_ulong(unsigned long number);
unsigned int print_hexa(long number);

#ifdef	ENABLE_BINARY
#define ENABLE_BINARY_
unsigned int print_binary(long number, unsigned int bits);
#endif

#ifdef ENABLE_FLOAT
#define ENABLE_FLOAT_

#ifdef	PRECISION_FLOAT
#define PRECISION_FLOAT_
unsigned int print_float(double number, int dp);
unsigned int print_scientific(double number, int dp);
#else
unsigned int print_float(float number, int dp);
unsigned int print_scientific(float number, int dp);
#endif
#endif


#ifdef	PRECISION_FLOAT_
//void embedded_string2number(char *string, double *number);
void embedded_string2number(unsigned char *string, double *number);
#else
//void embedded_string2number(char *string, float *number);
void embedded_string2number(unsigned char *string, float *number);
#endif


//#define		ENABLE_PAD								// enable padding in functions
//#define		ENABLE_FLOAT							// enable print float/double
//#define		PRECISION_FLOAT							// select precision version - use double variable
//#define		ENABLE_EXTRA_DECIMAL_PLACE				// enabled = 9 dp, disabled = 4 dp
//#define		ENABLE_BINARY							// enable binary notation

#define		BINARY			2						// number identificator
#define		DECIMAL			10
#define		HEXADEC			16

#define		SIGNED 			1						// if signed (+/-)
#define		NON_SIGNED		0						// just (+)
#define		NON_PAD			0						// withou padding
#define		UPPER_CASE		'A'
#define		LOWER_CASE		'a'

#define		SCI				1						// scientific notation "xx.yyezz"
#define		NON_SCI			0						// standard notation "xx.yy"

#define 	PAD_RIGHT		0x01					// right justified
#define 	PAD_ZERO		0x02					// padding with zero "0"

#define		PRINT_BUF_LEN 	36						// size of internl buffer to the conversion

//#define		WITH_LABEL		1
//#define		WITHOUT_LABEL	0


#endif
