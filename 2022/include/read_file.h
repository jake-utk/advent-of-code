/* Header file for read_file
 */
#include <stdio.h>

#define MAX_CHARS 1024
#define NUM_PTRS 2

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Struct containing a pointer to an open, given input file steam and the
 * data points needed to manage and access its contents.
 *
 * Attributes:
 *     stream: A pointer to a FILE stream, ideally the return of fopen() or
 *     stdin.
 *     lines:  A pointer to a pointer of chars, which functions as an array of
 *     string buffers containing each line of the input file.
 *     num_ptrs:  An integer count of the number of allocated pointers, which
 *     represent an empty slot for a line from the input file.
 *     used:  An integer count of the number of used pointer slots.
 */
struct File {
    FILE *stream;
    char **lines;
    int num_ptrs,
        used;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Reads given file stream line by line into File struct; returns pointer to
 * created struct.
 *
 * Args:
 *     file_name:  A FILE stream; ideally stdin or the return of fopen().
 * Returns:
 *     Pointer to File struct containing each line of filestream's contents.
 */
struct File *read_file(FILE *file_name);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Closes and frees given struct's filestream and memory.
 *
 * Args:
 *     current_file:  A File struct that has been opened and exists in memory.
 */
void close_file(struct File *current_file);
