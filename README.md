# Embedded_Printf

Embedded version of the famous "printf( )" function.

>This code is based in the code shared in this link: http://e2e.ti.com/support/development_tools/code_composer_studio/f/81/p/30479/107146

The idea is create an simple and efficient library to meet some common needs in embedded systems, as:
- convert numbers to strings
- send strings over serial port
- convert a string into number

To maintain the ballance between code size, speed and functionalities it's possible to do little changes in the code using C preprocessor.
- enable padding
- enable float number
- increase precision (using double)
- enable extra decimal places
- enable binary notation

All of this commenting/uncommenting the preprocessors.

The famous "printf( )" functions is named as "embedded_printf( )" and use a similar sintax as the original function with some reductions.

Besides the "embedded_printf( )" there are a simple version of each principal function. This can be useful when the traditional sintax is not required or when the speed of code/size is more important.


>To facilitate the portability the code is modular and the configuration of the serial port is done in separate files ("serial_conf.h" and "serial_conf.c").

> If possible contribute sending bug repports, new functions or porting the library to new devices.

#### Devices list (Ported)
MSP430
> MSP430G2553 (launchpad valueline), MSP430FR6989 (Launchpad EXP430FR6989)
#### Future Devices
More MSP430's, MSP432, Stellaris/Tiva

#### Bellow there is a list of the functions implemented:

``` c
// similar to the "printf( )"
int embedded_printf(char *format, ...);
```

``` c
// Print a String in the serial port
int embedded_prints(char *string, unsigned int width, unsigned int pad);
```

``` c
// Convert an integer number (signed or unsigned) with max size of 32bits (long) to array
int embedded_ltoa(char *print_buf, signed long input, unsigned int base, unsigned int sg, unsigned int width, unsigned int pad, unsigned char letbase);
```

``` c
// convert convert a float number to array - two versions defined by the preprocessors
int embedded_ftoa(char *print_buf, double input, signed int dp, unsigned int sci);
int embedded_ftoa(char *print_buf, float input, signed int dp, unsigned int sci);
```


#### Simple Functions to print data over serial

``` c
// simple function to print a String
unsigned int print_string(char *string);
```

``` c
// simple function to print a signed long
unsigned int print_long(long number);
```

``` c
// simple function to print a unsigned long
unsigned int print_ulong(unsigned long number);
```

``` c
// simple function to print a hexadecimal;
unsigned int print_hexa(long number);
```

``` c
// simple function to print a binary
unsigned int print_binary(long number, unsigned int bits);
```

``` c
// simple function to print a float/double  - two versions defined by the preprocessors
unsigned int print_float(double number, int dp);
unsigned int print_float(float number, int dp);
```

``` c
// simple function to print in scientific notatio - two versions defined by the preprocessors
unsigned int print_scientific(double number, int dp);
unsigned int print_scientific(float number, int dp);
```


#### Miscs

``` c
// convert string to float number - two versions defined by the preprocessors
void embedded_string2number(unsigned char *string, double *number);
void embedded_string2number(unsigned char *string, float *number);
```

``` c
// Call the specific function to send data
void putChar(unsigned char byte);
```

``` c
// return n lines in the terminal
void linesUp(unsigned char lines);
```

### Performance comparison
To evaluate the performance I compared the time taken to perform the "Embedded_printf" functions with the "printf" function native in the compiler Code Composer Studio. (More tips how do this in this website: http://processors.wiki.ti.com/index.php/Printf_support_for_MSP430_CCSTUDIO_compiler). The test was performed using the Launchpad EXP430FR6989.

##### Minimal Version (string, unsigned number and hex number)
* CCS native
* > RAM: 368 bytes - FRAM: 160 bytes - FRAM2: 1574 bytes - time(ms): 36.09
* Embedded_Printf
* > RAM: 160 bytes - FRAM: 72 bytes - FRAM2: 1238 bytes - time(ms): 36.05
* Embedded_Printf (different style)
* > RAM: 160 bytes - FRAM: 60 bytes - FRAM2: 800 bytes - time(ms): 36.07

##### Float number enabled (string, unsigned number, hex number, float and sci notation with 4dp)
* CCS native
* > RAM: 682 bytes - FRAM: 512 bytes - FRAM2: 15348 bytes - time(ms): 75.6
* Embedded_Printf
* > RAM: 160 bytes - FRAM: 98 bytes - FRAM2: 3368 bytes - time(ms): 70.4
* Embedded_Printf (different style)
* > RAM: 160 bytes - FRAM: 74 bytes - FRAM2: 2664 bytes - time(ms): 70.4



### To do:
- enable to configure library inside the main.c (or similar)
