#include "main.h"


/**
 * printfUnsigned - function that prints an unsigned number
 * 
 * @listType: a list a of arguments
 * @buffer: buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */
int printfUnsigned(va_list listType, char buffer[],int flags, int width, int precision, int size)
{
        int i = BUFFER_SIZE - 2;
        unsigned long int num = va_arg(listType, unsigned long int);

        num = convertSizeUnsigned(num, size);
        if (num == 0)
                buffer[i--] = '0';
        buffer[BUFFER_SIZE - 1] = '\0';
        while (num > 0)
        {
                buffer[i--] = (num % 10) + '0';
                num /= 10;
        }
        i++;
        return (writeUnsigned(0, i, buffer, flags, width, precision, size));
}

/**
 * printfOctal - function that prints an unsigned number in octal notation
 * 
 * @listType: a list of arguments
 * @buffer: the buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */
int printfOctal(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        int i = BUFFER_SIZE - 2;
        unsigned long int num = va_arg(listType, unsigned long int);
        unsigned long int temp = num;

        UNUSED(width);

        num = convertSizeUnsigned(num, size);
        if (num == 0)
                buffer[i--] = '0';
        buffer[BUFFER_SIZE - 1] = '\0';
        while (num > 0)
        {
                buffer[i--] = (num % 8) + '0';
                num /= 8;
        }
        if (flags & HASH && temp != 0)
                buffer[i--] = '0';
        i++;
        return (writeUnsigned(0, i, buffer, flags, width, precision, size));
}


/**
 * printfHexadecimal - function that prints an unsigned number in hexadecimal notation
 * 
 * @listType: a list of arguments
 * @buffer: the buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */
int printfHexadecimal(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        return (printfHexa(listType, "0123456789abcdef", buffer, flags, 'x', width, precision, size));
}


/**
 * printfHexaUpper - function that prints an unsigned number in upper case hexadecimal notation
 * 
 * @listType: a list of arguments
 * @buffer: the buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */
int printfHexaUpper(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        return (printfHexa(listType, "0123456789ABCDEF", buffer, flags, 'X', width, precision, size));
}


/**
 * printHexa - function that prints an hexadecimal number in lowercase or uppercase
 * corespending the mapto and flagCh
 * 
 * @listType: Lista of arguments
 * @mapto: an array of values to map the number to
 * @buffer: the buffer array to handle print
 * @flags:  to calculates active flags
 * @flagCh: to calculates active flags
 * @width: to get the width
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */

int printfHexa(va_list listType, char mapto[], char buffer[], int flags, char flagCh, int width, int precision, int size)
{
        int i = BUFFER_SIZE - 2;
        unsigned long int num = va_arg(listType, unsigned long int);
        unsigned long int temp = num;

        UNUSED(width);

        num = convertSizeUnsigned(num, size);
        if (num == 0)
                buffer[i--] = '0';
        buffer[BUFFER_SIZE - 1] = '\0';
        while (num > 0)
        {
                buffer[i--] = mapto[num % 16];
                num /= 16;
        }
        if (flags & HASH && temp != 0)
        {
                buffer[i--] = flagCh;
                buffer[i--] = '0';
        }
        i++;
        return (writeUnsigned(0, i, buffer, flags, width, precision, size));
}