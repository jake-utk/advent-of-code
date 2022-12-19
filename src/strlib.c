#include <stdlib.h>
#include <stdio.h>
#include <string.h>


size_t strnlen(const char *str, size_t max)
{
    const char *end = memchr(str, 0, max);
    return end ? (size_t) (end - str) : max;
}


char *safer_strcpy(char *source, char *dest, int dest_size)
{
    if (dest_size > 0)
    {
        dest[0] = '\0';
        strncat(dest, source, dest_size - 1);
    }
    return dest;
}


char *strdup(const char *source)
{
    char *dest = malloc(strlen(source) + 1);  // Space for length plus nul
    if (dest == NULL) return NULL;

    strcpy(dest, source);                     // Copy the characters

    return dest;
}
