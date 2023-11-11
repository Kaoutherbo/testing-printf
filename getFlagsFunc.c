
#include "main.h"


/**
 * getFlags - function that calculates the active flags
 * 
 * Description: This function extracts and returns formatting
 * flags from a string starting at the position specified by
 * the integer pointer i, using predefined flags and characters.
 * It updates i to the last processed index and returns the flags as an integer.
 * 
 * @format: the formatted string in which to print the arguments
 * @i: take a parameter.
 * 
 * Return: calculated flags are then returned as an integer.
 */
int getFlags(const char *format, int *i)
{
        const int FLAGS_ARR[] = {MINUS, PLUS, ZERO, HASH, SPACE, 0};
        const char FLAGS_CHS[] = {'-', '+', '0', '#', ' ', '\0'};
        int flags = 0, j, currInx;

        for (currInx = *i + 1; format[currInx] != '\0'; currInx++)
        {
                for (j = 0; FLAGS_CHS[j] != '\0'; j++)
                        if (format[currInx] == FLAGS_CHS[j])
                        {
                                flags |= FLAGS_ARR[j];
                                break;
                        }
                if (FLAGS_CHS[j] == 0)
                        break;
        }
        *i = currInx - 1;
        return (flags);
}
