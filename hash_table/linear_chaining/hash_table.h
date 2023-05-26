#pragma once


struct hash_table_node {
    const char *key;
    const void *value;
    struct hash_table_node *ptr_next;
};

struct hash_table {
    int size;
    int el_num;
    struct hash_table_node **array;
};

enum hash_table_status {
    HASH_TABLE_STATUS_SUCCESS = 0,
    HASH_TABLE_STATUS_ERROR = 1,
    HASH_TABLE_STATUS_NOT_FOUND = 2,
    HASH_TABLE_STATUS_OUT_OF_MEMORY = 3,
    HASH_TABLE_STATUS_INVALID_ARGUMENT = 4,
    HASH_TABLE_STATUS_FULL = 5,
};

// hash_table_new creates and returns an empty hash table
enum hash_table_status
hash_table_new(struct hash_table **map);

// hash_table_insert takes the map and inserts the new key&value pair into it
enum hash_table_status
hash_table_insert(struct hash_table *map, const char *key, const void *value);

// hash_table_remove removes the value of the given key. 
// it will return NOT_FOUND if the key could not be found
enum hash_table_status
hash_table_remove(struct hash_table *map, const char *key);

// hash_table_print prints the content of the hash table
void
hash_table_print(const struct hash_table *map, void (*value_printer)(const void *));
