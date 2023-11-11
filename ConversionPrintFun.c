#include "main.h"

/**
 * printfChar -function that  prints a char
 * 
 * @listType: a list a of arguments
 * @buffer: a buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */
int printfChar(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        char ch = va_arg(listType, int);
        return (handleWriteChar(ch, buffer, flags, width, precision, size));
}

/**
 * printfString - function that prints a string
 * 
 * @listType: a list of arguments
 * @buffer: the buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width.
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */
int printfString(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        int len = 0, i;
        char *str = va_arg(listType, char *);

        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);
        if (str == NULL)
        {
                str = "(null)";
                if (precision >= 6)
                        str = "      ";
        }


        while (str[len] != '\0')
                len++;


        if (precision >= 0 && precision < len)
                len = precision;


        if (width > len)
        {
                if (flags & MINUS)
                {
                        write(1, &str[0], len);
                        for (i = width - len; i > 0; i--)
                                write(1, " ", 1);
                        return (width);
                }
                else
                {
                        for (i = width - len; i > 0; i--)
                                write(1, " ", 1);
                        write(1, &str[0], len);
                        return (width);
                }
        }


        return (write(1, str, len));
}

/**
 * printfPercentSign - function that prints a percent sign
 * 
 * @listType: a list of arguments
 * @buffer: the buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width.
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */
int printfPercentSign(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        UNUSED(listType);
        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);
        return (write(1, "%%", 1));
}


/**
 * print_int - function that prints an integer number
 * 
 * @listType: a list of arguments
 * @buffer: buffer array to handle print
 * @flags:  to calculates active flags
 * @width: get the  width.
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: number of characters or bytes printed
 */
int printfInteger(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        int i = BUFFER_SIZE - 2;
        int isNegative = 0;
        long int numbers = va_arg(listType, long int);
        unsigned long int num;

        numbers = convertSizeNumber(numbers, size);
        if (numbers == 0)
                buffer[i--] = '0';
        buffer[BUFFER_SIZE - 1] = '\0';
        num = (unsigned long int)numbers;
        if (numbers < 0)
        {
                num = (unsigned long int)((-1) * numbers);
                isNegative = 1;
        }
        while (num > 0)
        {
                buffer[i--] = (num % 10) + '0';
                num /= 10;
        }
        i++;
        return (writeNumber(isNegative, i, buffer, flags, width, precision, size));
}


/**
 * printfBinary - function that prints an unsigned binary number
 * this function convert a number into its representation in binary
 * 
 * @listType: a list of arguments
 * @buffer: the buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width.
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
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