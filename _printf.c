#include "main.h"

/**
 * printBuffer - procedure that prints the contents of the buffer if it exist
 * 
 * Description: this procedure prints the contents of a character 
 * array up to a specified index if the buffer is non-empty.
 * The index represents the length of the content 
 * to be printed.After printing, the index is reset to zero.
 * 
 * @buffer: Array of chars
 * @buffIndx: Index at which to add next char, represents the length.
 * Return: void
 */
void printBuffer(char buffer[], int *buffIndx)
{
        if (*buffIndx > 0)
                write(1, &buffer[0], *buffIndx);
        *buffIndx = 0;
}

/**
 * _printf - is an implementation of the printf function
 * it can print anything
 * 
 * Description: this function print various types of data. It processes
 * the format string, handling placeholders and formatting options.
 * The characters are stored in a buffer and printed in chunks for
 * efficiency. The function returns the total number of printed characters.
 * 
 * @format: format pointer.
 * Return: the total number of printed characters.
 */
int _printf(const char *format, ...)
{
        int i, isPrinted = 0, countCh = 0;
        int flags, width, precision, size, buffIndx = 0;
        
        va_list list;
        char buffer[BUFFER_SIZE];
        if (format == NULL)
                return (-1);
        va_start(list, format);
                i = 0;
        while (format && format[i] != '\0')
        {
                if (format[i] != '%')
                {
                        buffer[buffIndx++] = format[i];
                        if (buffIndx == BUFFER_SIZE)
                                printBuffer(buffer, &buffIndx);
                        countCh++;
                }
                else
                {
                        printBuffer(buffer, &buffIndx);
                        flags = getFlags(format, &i);
                        width = getWidth(format, &i, list);
                        precision = getPrecision(format, &i, list);
                        size = getSize(format, &i);
                        ++i;
                        isPrinted = handlePrint(format, &i, list, buffer, flags, width, precision, size);
                        if (isPrinted == -1)
                                return (-1);
                        countCh += isPrinted;
                }
                i++;
        }
        printBuffer(buffer, &buffIndx);
        va_end(list);
        return (countCh);
}