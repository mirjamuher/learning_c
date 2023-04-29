#pragma once

struct book {
    char *title;
    char *author;
    int num_of_pages;
};

unsigned int 
num_of_books_written(const char *name);

void
add_book(const struct book *new_book);
