#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "books.h"

// static makes `books` a file-level variable (as opposed to a global one)
static struct book *books = NULL;
static unsigned int nbooks = 0;

unsigned int 
num_of_books_written(const char *name) {
    int i;
    unsigned int count = 0;
    for (i = 0; i < nbooks; i++) {
        const struct book *crnt_book = &books[i];
        char *author = crnt_book->author;
        if (strcmp(author, name) == 0) {
            count++;
        }
    }
    return count;
}

void
add_book(const struct book *new_book) {
    // step 1: calc & alloc new needed size in memory
    size_t size_of_book = sizeof(struct book);
    size_t books_size = (size_of_book * nbooks);
    struct book *new_books_array = NULL;
    new_books_array = malloc(books_size + size_of_book);
    assert(new_books_array != NULL);

    // step 2: store all existing books plus new book 
    memcpy(new_books_array, books, books_size);
    memcpy(&new_books_array[nbooks], new_book, size_of_book);

    // step 3: free up memory that the old array it
    free(books);

    // step 4: increment the size & overwrite the file-level variable
    nbooks++;
    books = new_books_array;
}
