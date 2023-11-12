#include "main.h"


/**
 * printfBinary - function that prints an unsigned binary number
 * 
 * Description:  this function prints an unsigned binary number, converting the
 * input number into its binary representation. It calculates the
 * binary digits, skips leading zeros, and writes the binary representation
 * to the output.
 * 
 * @listType: a list of arguments
 * @buffer: the buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width.
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of characters printed
 */
int printfBinary(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        unsigned int num, k, i, sum;
        unsigned int a[32];
        int count;

        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);


        num = va_arg(listType, unsigned int);
        k = 2147483648; 
        a[0] = num / k;
        i = 1;
        while( i < 32)
        {
                k /= 2;
                a[i] = (num / k) % 2;
                i++;
        }
        i = 0, sum = 0, count = 0;
        while ( i < 32)
        {
                sum += a[i];
                if (sum || i == 31)
                {
                        char z = '0' + a[i];


                        write(1, &z, 1);
                        count++;
                }
                i++;
        }
        return (count);
}

/**
 * printfOctal - function that prints an unsigned number in octal notation
 * 
 * Description: this function prints an unsigned number in octal notation, handling
 * various formatting options such as width, precision, and flags.
 * It converts the input number, processes each digit, and delegates
 * the printing task to writeUnsigned function.
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
 * Description: this function prints an unsigned number in lowercase hexadecimal notation.
 * It delegate the core printing functionality to printfHexa,
 * passing the appropriate character mapping for lowercase hex digits.
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
 * Description: this function prints an unsigned number in uppercase hexadecimal notation.
 * It delegate the core printing functionality to printfHexa,
 * passing the appropriate character mapping for uppercase hex digits.
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
 * 
 * Descrption: this function is a generic function for printing an unsigned number
 * in either lowercase or uppercase hexadecimal notation.
 * It handles the common logic for both printfHexadecimal and
 * printfHexaUpper. 
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