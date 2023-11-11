#include "main.h"

/**
 * printBuffer - procedure that prints the contents of the buffer if it exist
 * 
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
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
 * @format: format pointer.
 * Return: Printed chars.
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