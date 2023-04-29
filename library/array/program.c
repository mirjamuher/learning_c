#include <stdio.h>
#include <string.h>
#include "books.h"

int main() {
    struct book new_book = {
        "Mary Poppins",
        "Jne Doe",
        123,
    };

    add_book(&new_book);

    struct book new_new_book = {
        "Harry Potter",
        "She who shall not be named",
        2038434,
    };

    add_book(&new_new_book);

    struct book another_book = {
        "John's Story",
        "Jne Doe",
        2,
    };

    add_book(&another_book);

    struct book last_book = {
        "Coughing your lungs out",
        "Jim",
        2,
    };

    add_book(&last_book);

    unsigned int count = num_of_books_written("Jne Doe");
    printf("%d\n", count);
    return 0;
}
