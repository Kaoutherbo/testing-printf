
#include "main.h"


/**
 * getWidth - function that calculates the width for printing
 * 
 * Description: this function calculates the print width from a formatted string.
 * It processes digits and retrieves width from the argument list
 * if an asterisk (*) is encountered. The function updates the input
 * pointer i and returns the width.
 * 
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int getWidth(const char *format, int *i, va_list list)
{
        int currInx;
        int width = 0;

        for (currInx = *i + 1; format[currInx] != '\0'; currInx++)
        {
                if (isDigit(format[currInx]))
                {
                        width *= 10;
                        width += format[currInx] - '0';
                }
                else if (format[currInx] == '*')
                {
                        currInx++;
                        width = va_arg(list, int);
                        break;
                }
                else
                        break;
        }
        *i = currInx - 1;
        return (width);
}
