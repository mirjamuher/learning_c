#include "hash_table.h"
#include <stdio.h>

int main(void) {
    enum hash_table_status status;

    // create a new hash_table
    struct hash_table *map = NULL;
    status = hash_table_new(&map);
    printf("created a new map, status is: %d \n", status);

    // insert some values
    status = hash_table_insert(map, "duck", "quack");
    printf("inserted, status is: %d \n", status);

    status = hash_table_insert(map, "dog", "woof");
    printf("inserted, status is: %d \n", status);

    status = hash_table_insert(map, "cat", "meow");
    printf("inserted, status is: %d \n", status);

    status = hash_table_remove(map, "duck");
    printf("deleted, status is: %d \n", status);

    status = hash_table_insert(map, "duck", "quack");
    printf("inserted, status is: %d \n", status);

    return 0;
}
