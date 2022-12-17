#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


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

size_t strnlen(const char *str, size_t max) {
    const char *end = memchr(str, 0, max);
    return end ? (size_t) (end - str) : max;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Replacement for stdlib's strcpy, allowing the user to specify the max to
 * copy while also always nul-terminating the string.
 *
 * strcpy depends on a nul-terminator '\0' so it knows when to stop; if it
 * isn't present then it will overflow.
 *
 * strncpy prevents the above by accepting a max, but it won't add a
 * nul-terminator to the destination string if it has completely filled the
 * max.
 *
 * Args:
 *     str: Pointer to first element of a constant string.
 *     max: Integer denoting max fallback size of string.
 * Returns:
 *     Integer representation of string's length.
 */

char *safer_strcpy(char *source, char *dest, int dest_size) {
    if (dest_size > 0)
    {
        dest[0] = '\0';
        strncat(dest, source, dest_size - 1);
    }
    return dest;
}
