#include <stdio.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Replacement for stdlib's strlen, which is not safe if the buffer is null
 * terminated.  Returns the integer size of the string.
 *
 * Args:
 *     str: Pointer to first element of a constant string.
 *     max: Integer denoting max fallback size of string.
 * Returns:
 *     Integer representation of string's length.
 */
size_t strnlen(const char *str, size_t max);
