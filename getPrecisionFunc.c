
#include "main.h"


/**
 * getPrecision - this function calculates the precision for printing
 * 
 * Description: this function calculates and returns the print precision
 * from a formatted string.It processes digits and retrieves precision
 * from the argument list if an asterisk (*) is found. The function updates
 * the input pointer i and returns the precision,
 * defaulting to -1 if not specified.
 * 
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: the precision.
 */
int getPrecision(const char *format, int *i, va_list list)
{
        int currInx = *i + 1;
        int precision = -1;

        if (format[currInx] != '.')
                return (precision);
        precision = 0;
        for (currInx += 1; format[currInx] != '\0'; currInx++)
        {
                if (isDigit(format[currInx]))
                {
                        precision *= 10;
                        precision += format[currInx] - '0';
                }
                else if (format[currInx] == '*')
                {
                        currInx++;
                        precision = va_arg(list, int);
                        break;
                }
                else
                        break;
        }
        *i = currInx - 1;
        return (precision);
}
