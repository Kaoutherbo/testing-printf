#include "main.h"

/**
 * handleWriteChar - function that prints a string
 * 
 * Description: this function prints a character with specified
 * formatting to a character array. The character is
 * stored at the left, and padding is added to the
 * buffer's right based on flags, width, and precision.
 * 
 * @ch: char type.
 * @buffer: the buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: to get the width.
 * @precision: the precision specifier
 * @size: the size of specifier
 *
 * Return: the number of characters printed.
 */
int handleWriteChar(char ch, char buffer[], int flags, int width, int precision, int size)
{ 
        int i = 0;
        char padd = ' ';

        UNUSED(precision);
        UNUSED(size);

        if (flags & ZERO)
                padd = '0';
        buffer[i++] = ch;
        buffer[i] = '\0';
        if (width > 1)
        {
                buffer[BUFFER_SIZE - 1] = '\0';
                for (i = 0; i < width - 1; i++)
                        buffer[BUFFER_SIZE - i - 2] = padd;
                if (flags & MINUS)
                        return (write(1, &buffer[0], 1) +
                                        write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
                else
                        return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
        }
        return (write(1, &buffer[0], 1));
}


/**
 * writeNum - function that writes a number using a bufffer
 * 
 * Description: Writes a number to a buffer with specified formatting.
 * and handles flags, width, precision, size, and additional characters.
 * 
 * @ind: Index at which the number starts on the buffer
 * @buffer: a buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width.
 * @precision: the precision specifier
 * @size: the size specifier
 * @length: Number length
 * @padd: Pading char
 * @ch: Extra char
 *
 * Return: the number of characters printed.
 */
int writeNum(int ind, char buffer[], int flags, int width, int precision, int length, char padd, char ch)
{
        int i, paddBegin = 1;


        if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0' && width == 0)
                return (0); 
        if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
                buffer[ind] = padd = ' '; 
        if (precision > 0 && precision < length)
                padd = ' ';
        while (precision > length)
                buffer[--ind] = '0', length++;
        if (ch != 0)
                length++;
        if (width > length)
        {
                for (i = 1; i < width - length + 1; i++)
                        buffer[i] = padd;
                buffer[i] = '\0';
                if (flags & MINUS && padd == ' ')
                {
                        if (ch)
                                buffer[--ind] = ch;
                        return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
                }
                else if (!(flags & MINUS) && padd == ' ')
                {
                        if (ch)
                                buffer[--ind] = ch;
                        return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
                }
                else if (!(flags & MINUS) && padd == '0')
                {
                        if (ch)
                                buffer[--paddBegin] = ch;
                        return (write(1, &buffer[paddBegin], i - paddBegin) +
                                write(1, &buffer[ind], length - (1 - paddBegin)));
                }
        }
        if (ch)
                buffer[--ind] = ch;
        return (write(1, &buffer[ind], length));
}


/**
 * writeNumber - function that prints a string
 * 
 * Description: Writes a formatted number to a buffer.
 * and considers flags, width, precision, and size.
 * 
 * @isNegative: a list of arguments
 * @ind: index.
 * @buffer: a buffer array to handle print
 * @flags:  to calculates active flags
 * @width: to get the width.
 * @precision: the precision specifier
 * @size: the size specifier
 *
 * Return: the number of characters printed.
 */
int writeNumber(int isNegative, int ind, char buffer[], int flags, int width, int precision, int size)
{
        int len = BUFFER_SIZE - ind - 1;
        char padd = ' ', ch = 0;

        UNUSED(size);

        if ((flags & ZERO) && !(flags & MINUS))
                padd = '0';
        if (isNegative)
                ch = '-';
        else if (flags & PLUS)
                ch = '+';
        else if (flags & SPACE)
                ch = ' ';
        return (writeNum(ind, buffer, flags, width, precision, len, padd, ch));
}


/**
 * writeUnsigned - function that writes an unsigned number
 * 
 * Description: Writes an unsigned number to a buffer.
 * and handles flags, width, precision, and size.
 * 
 * @isNegative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int writeUnsigned(int isNegative, int ind, char buffer[], int flags, int width, int precision, int size)
{
        int len = BUFFER_SIZE - ind - 1, i = 0;
        char padd = ' ';

        UNUSED(isNegative);
        UNUSED(size);

        if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
                return (0);

        if (precision > 0 && precision < len)
                padd = ' ';
        while (precision > len)
        {
                buffer[--ind] = '0';
                len++;
        }

        if ((flags & ZERO) && !(flags & MINUS))
                padd = '0';


        if (width > len)
        {
                for (i = 0; i < width - len; i++)
                        buffer[i] = padd;


                buffer[i] = '\0';


                if (flags & MINUS) 
                {
                        return (write(1, &buffer[ind], len) + write(1, &buffer[0], i));
                }
                else
                {
                        return (write(1, &buffer[0], i) + write(1, &buffer[ind], len));
                }
        }


        return (write(1, &buffer[ind], len));
}


/**
 * writePointer - function that Writes a memory address
 * 
 * Description: Writes a memory address to a buffer,
 * and handles flags, width, and additional characters.
 * 
 * @buffer: an array of chars
 * @ind: the index at which the number starts in the buffer
 * @length: the length of number
 * @width: the width specifier
 * @flags: the flags specifier
 * @padd: a char variable that representing the padding
 * @ch: an char representing extra char
 * @paddBegin: Index at which padding should start
 *
 * Return: the number of written characters.
 */
int writePointer(char buffer[], int ind, int length, int width, int flags, char padd, char ch, int paddBegin)
{
        int i;


        if (width > length)
        {
                for (i = 3; i < width - length + 3; i++)
                        buffer[i] = padd;
                buffer[i] = '\0';
                if (flags & MINUS && padd == ' ')
                {
                        buffer[--ind] = 'x';
                        buffer[--ind] = '0';
                        if (ch)
                                buffer[--ind] = ch;
                        return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
                }
                else if (!(flags & MINUS) && padd == ' ')
                {
                        buffer[--ind] = 'x';
                        buffer[--ind] = '0';
                        if (ch)
                                buffer[--ind] = ch;
                        return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
                }
                else if (!(flags & MINUS) && padd == '0')
                {
                        if (ch)
                                buffer[--paddBegin] = ch;
                        buffer[1] = '0';
                        buffer[2] = 'x';
                        return (write(1, &buffer[paddBegin], i - paddBegin) + write(1, &buffer[ind], length - (1 - paddBegin) - 2));
                }
        }
        buffer[--ind] = 'x';
        buffer[--ind] = '0';
        if (ch)
                buffer[--ind] = ch;
        return (write(1, &buffer[ind], BUFFER_SIZE - ind - 1));
}