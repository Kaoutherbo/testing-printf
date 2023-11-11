
#include "main.h"

/**
 * printfPointer - function that prints the value of a pointer variable
 * 
 * @listType: List a of arguments
 * @buffer: a buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */
int printfPointer(va_list types, char buffer[], int flags, int width, int precision, int size)
{
        char ch = 0, padding = ' ';
        int ind = BUFFER_SIZE - 2, len = 2, paddbegin = 1; 
        unsigned long numAddrs;
        char mapto[] = "0123456789abcdef";
        void *addrs = va_arg(types, void *);

        UNUSED(width);
        UNUSED(size);

        if (addrs == NULL)
                return (write(1, "(nil)", 5));

        buffer[BUFFER_SIZE - 1] = '\0';
        UNUSED(precision);

        numAddrs = (unsigned long)addrs;
        while (numAddrs > 0)
        {
                buffer[ind--] = mapto[numAddrs % 16];
                numAddrs /= 16;
                len++;
        }
        if ((flags & ZERO) && !(flags & MINUS))
                padding = '0';
        if (flags & PLUS)
                ch = '+', len++;
        else if (flags & SPACE)
                ch = ' ', len++;
        ind++;
        return (writePointer(buffer, ind, len, width, flags, padding, ch, paddbegin));
}


/**
 * printfUnPrintable - function that prints the ascii codes in hexa of un printable characters
 * 
 * Description: non printable characters are the characters between (0 < ASCII value < 32 or >= 127) and they 
 * are printed this way: \x, followed by the ASCII code value 
 * in hexadecimal (upper case - always 2 characters)
 * 
 * @listType: List a of arguments
 * @buffer: a buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: the number of bytes or characters printed
 */
int printfUnPrintable(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        int i = 0, offset = 0;
        char *str = va_arg(listType, char *);

        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);

        if (str == NULL)
                return (write(1, "(null)", 6));


        while (str[i] != '\0')
        {
                if (isPrintable(str[i]))
                        buffer[i + offset] = str[i];
                else
                        offset += appendHexaCode(str[i], buffer, i + offset);


                i++;
        }


        buffer[i + offset] = '\0';


        return (write(1, buffer, i + offset));
}


/**
 * printfReverse - function that prints the reverse of a string.
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

int printfReverse(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        char *str;
        int i, count = 0;


        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(size);

        str = va_arg(listType, char *);
        if (str == NULL)
        {
                UNUSED(precision);
                str = ")Null(";
        }
        for (i = 0; str[i]; i++)
                ;
        for (i = i - 1; i >= 0; i--)
        {
                char z = str[i];
                write(1, &z, 1);
                count++;
        }
        return (count);
}


/**
 * printfRot13String - function that prints a string in rot13.
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
int printfRot13String(va_list listType, char buffer[], int flags, int width, int precision, int size)
{
        char temp;
        char *str;
        unsigned int i, j;
        int count = 0;
        char inputStr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char outputStr[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

        str = va_arg(listType, char *);
        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);

        if (str == NULL)
                str = "(AHYY)";
        for (i = 0; str[i]; i++)
        {
                for (j = 0; inputStr[j]; j++)
                {
                        if (inputStr[j] == str[i])
                        {
                                temp = outputStr[j];
                                write(1, &temp, 1);
                                count++;
                                break;
                        }
                }
                if (!inputStr[j])
                {
                        temp = str[i];
                        write(1, &temp, 1);
                        count++;
                }
        }
        return (count);
}
