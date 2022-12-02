#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    char *buffer = NULL;
    size_t buffer_size = 32;
    size_t line;

    fp = fopen("problem-1-input.txt", "r");
    if (NULL == fp) exit(EXIT_FAILURE);

    buffer = (char *)malloc(buffer_size * sizeof(char));
    if (NULL == buffer) {
        perror("Unable to allocate buffer");
        exit(EXIT_FAILURE);
    }

    while ((line = getline(&buffer, &buffer_size, &fp)) != -1)
        printf("%s", buffer);

    free(buffer);
    exit(EXIT_SUCCESS);
}
