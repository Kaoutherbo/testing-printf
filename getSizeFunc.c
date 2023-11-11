
#include "main.h"


/**
 * getSize - function that calculates the size to cast the argument
 * 
 * Description: this function calculates and returns
 * the argument size from a formatted string.
 * It checks for 'l' (long) or 'h' (short) qualifiers,
 * updates the input pointer i, and returns the determined size.
 * 
 * @format: formatted string in which to print the arguments
 * @i: a list of arguments to be printed.
 *
 * Return: the size.
 */

int getSize(const char *format, int *i)
{
        int currInx = *i + 1;
        int size = 0;

        if (format[currInx] == 'l')
                size = LONG_SIZE;
        else if (format[currInx] == 'h')
                size = SHORT_SIZE;
        if (size == 0)
                *i = currInx - 1;
        else
                *i = currInx;
        return (size);
}
