#include "main.h"

/**
 * handlePrint - this function prints an argument based on its type
 * 
 * Description: this function prints an argument based on its type using
 * a format string. It employs a structure with format
 * specifiers and corresponding printing functions.
 * The function returns the number of characters printed,
 * considering special cases like '%', and takes parameters
 * for flags, width, precision, and size.
 * 
 * @frmt: the formatted string in which to print the arguments.
 * @list: a list of arguments to be printed.
 * @ind: index.
 * @buffer: a buffer array to handle print.
 * @flags: to calculates active flags
 * @width: to get the width.
 * @precision: the precision specification
 * @size: the size specifier
 * 
 * Return: number of characters printed
 */
int handlePrint(const char *frmt, int *ind, va_list list, char buffer[], int flags, int width, int precision, int size)
{
        fmt_t formatTypes[] = {
                {'c', printfChar},
                {'s', printfString},
                {'%', printfPercentSign},
                {'i', printfInteger},
                {'d', printfInteger},
                {'b', printfBinary},
                {'u', printfUnsigned},
                {'o', printfOctal},
                {'x', printfHexadecimal},
                {'X', printfHexaUpper},
                {'p', printfPointer},
                {'S', printfUnPrintable},
                {'r', printfReverse},
                {'R', printfRot13String},
                {'\0', NULL}
        };
        int i, unLen = 0, printedCh = -1;

        for (i = 0; formatTypes[i].format != '\0'; i++)
                if (frmt[*ind] == formatTypes[i].format)
                        return (formatTypes[i].func(list, buffer, flags, width, precision, size));

        if (formatTypes[i].format == '\0')
        {
                if (frmt[*ind] == '\0')
                        return (-1);
                unLen += write(1, "%%", 1);
                if (frmt[*ind - 1] == ' ')
                        unLen += write(1, " ", 1);
                else if (width)
                {
                        --(*ind);
                        while (frmt[*ind] != ' ' && frmt[*ind] != '%')
                                --(*ind);
                        if (frmt[*ind] == ' ')
                                --(*ind);
                        return (1);
                }
                unLen += write(1, &frmt[*ind], 1);
                return (unLen);
        }
        return (printedCh);
}