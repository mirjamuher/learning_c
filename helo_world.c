#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Two arguments required, got %d.\n", argc - 1);
        return 1;
    }

    char *result = NULL;
    size_t var1len = strlen(argv[1]);
    size_t var2len = strlen(argv[2]);
    result = (char *)malloc(var1len + var2len + 2);
    assert(result == NULL); 

    memcpy(result, argv[1], var1len);
    memcpy(&result[var1len], "-", 1);
    memcpy(&result[var1len + 1], argv[2], var2len + 1);

    printf("%s\n", result);

    free(result);

    return 0;
}
