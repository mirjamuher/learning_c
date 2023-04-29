#include <stdio.h>
#include <string.h>
#include "books.h"

int main(void) {
    // create 4 books
    struct book mary_poppins = {
        "Mary Poppins",
        "Jne Doe",
        123,
    };

    add_book(&mary_poppins);
    printf("book count (1): %d\n", book_cnt());

    struct book harry_potter = {
        "Harry Potter",
        "She who shall not be named",
        2038434,
    };

    add_book(&harry_potter);
    printf("book count (2): %d\n", book_cnt());

    struct book johns_story = {
        "John's Story",
        "Jne Doe",
        2,
    };

    add_book(&johns_story);
    printf("book count(3): %d\n", book_cnt());

    struct book coughing_book = {
        "Coughing your lungs out",
        "Jim",
        2,
    };
    add_book(&coughing_book);
    printf("book count (4): %d\n", book_cnt());

    // count how many of them were written by Jne Doe
    unsigned int count = num_of_books_written("Jne Doe");
    printf("books found (2): %d\n", count);

    // delete books one by one
    delete_book(&johns_story);
    printf("book count (3): %d\n", book_cnt());
    unsigned int count2 = num_of_books_written("Jne Doe");
    printf("books found (1): %d\n", count2);

    delete_book(&mary_poppins);
    printf("book count (2): %d\n", book_cnt());
    unsigned int count3 = num_of_books_written("Jne Doe");
    printf("books found (0): %d\n", count3);

    delete_book(&coughing_book);
    printf("book count (1): %d\n", book_cnt());

    delete_book(&coughing_book);
    printf("book count (1): %d\n", book_cnt());

    delete_book(&harry_potter);
    printf("book count (0): %d\n", book_cnt());
    return 0;
}
