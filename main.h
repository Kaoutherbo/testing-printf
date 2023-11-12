#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>


#define UNUSED(x) (void)(x)
#define BUFFER_SIZE 1024


#define MINUS 1
#define PLUS 2
#define ZERO 4
#define HASH 8
#define SPACE 16


#define LONG_SIZE 2
#define SHORT_SIZE 1


/**
 * struct format - Struct operation
 *
 * @format: represents the format character.
 * @func: represents a pointer to the function
 * associated with the format character.This function
 * takes a variable argument list (va_list) and other
 * formatting parameters,then performs the necessary printing operation.
 */
struct format
{
        char format;
        int (*func)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct format format_t - Struct op
 *
 * @format: The format structure.
 * @format_t: the new name of format strcture.
 */
typedef struct format format_t;

int printfChar(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfString(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfPercentSign(va_list listType, char buffer[], int flags, int width, int precision, int size);

int printfInteger(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfBinary(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfUnsigned(va_list listType, char buffer[],int flags, int width, int precision, int size);
int printfOctal(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfHexadecimal(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfHexaUpper(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfHexa(va_list listType, char map_to[], char buffer[], int flags, char flag_ch, int width, int precision, int size);
int printfUnPrintable(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfPointer(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfReverse(va_list listType, char buffer[], int flags, int width, int precision, int size);
int printfRot13String(va_list listType, char buffer[], int flags, int width, int precision, int size);

int getFlags(const char *format, int *i);
int getWidth(const char *format, int *i, va_list list);
int getPrecision(const char *format, int *i, va_list list);
int getSize(const char *format, int *i);

void printBuffer(char buffer[], int *buffIndx);
int handlePrint(const char *fmt, int *ind, va_list list, char buffer[], int flags, int width, int precision, int size);

int handleWriteChar(char c, char buffer[], int flags, int width, int precision, int size);
int writeNumber(int isPositive, int ind, char buffer[], int flags, int width, int precision, int size);
int writeNum(int ind, char bff[], int flags, int width, int precision, int length, char padd, char extra_c);
int writePointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start);
int writeUnsigned(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size);

bool isPrintable(char);
int appendHexaCode(char, char[], int);
bool isDigit(char);
long int convertSizeNumber(long int num, int size);
long int convertSizeUnsigned(unsigned long int num, int size);

int _printf(const char *format, ...);

#endif /* MAIN_H */
