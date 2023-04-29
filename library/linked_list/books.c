#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "books.h"
#include "linked_list.h"

// static makes `books` a file-level variable (as opposed to a global one)
    static struct linked_list_node *books = NULL;

unsigned int 
num_of_books_written(const char *name) {
    unsigned int count = 0;
    struct linked_list_node *b = books;
    for ( ; b != NULL; b = b->ptr_nxt) {
        const struct book *crnt_book = b->data;
        char *author = crnt_book->author;
        if (strcmp(author, name) == 0) {
            count++;
        }
    }
    return count;
}

void
add_book(const struct book *new_book) {
    static struct linked_list_node **ptr_to_books_head = &books;
    enum linked_list_status status = linked_list_append(new_book, ptr_to_books_head);
    if (status == LINKED_LIST_STATUS_SUCCESS) {
        books = *ptr_to_books_head;
    }
}

void
delete_book(const struct book *book) {
    static struct linked_list_node **ptr_to_books_head = &books;
    enum linked_list_status status = linked_list_delete_element(book, ptr_to_books_head);
    if (status == LINKED_LIST_STATUS_SUCCESS) {
        books = *ptr_to_books_head;
    }
}

unsigned int
book_cnt(void) {
    return linked_list_size(books);
}
