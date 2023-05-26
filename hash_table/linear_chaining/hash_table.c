#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

static const int HASH_TABLE_INIT_SIZE = 7;
static const float HASH_TABLE_LOAD_FACTOR = 0.7;

static unsigned long
hash_string(const char *str) {
    // implements dbj2 algorithm
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

// hash_table_new creates and returns an empty hash table
enum hash_table_status
hash_table_new(struct hash_table **map) {
    // allocate memory on the heap for the hash_table so it persists after function exits
    struct hash_table *new_map = malloc(sizeof(struct hash_table));
    if (new_map == NULL) {
        return HASH_TABLE_STATUS_OUT_OF_MEMORY;
    }

    // fill hash_table info i have so far
    new_map->size = HASH_TABLE_INIT_SIZE;
    new_map->el_num = 0;

    // allocate memory to the array and set all values to 0
    new_map->array = malloc(sizeof(struct hash_table_node *) * new_map->size);
    if (new_map->array == NULL) {
        return HASH_TABLE_STATUS_OUT_OF_MEMORY;
    }
    memset(new_map->array, 0, sizeof(struct hash_table_node *) * new_map->size);

    // set map value to new_map address
    *map = new_map;
    return HASH_TABLE_STATUS_SUCCESS;
}

// hash_table_insert takes the map and inserts the new key&value pair into it
enum hash_table_status
hash_table_insert(struct hash_table *map, const char *key, const void *value) {
    // check if we are getting bigger than the load factor with this new element
    if ((map->el_num + 1) >= (map->size * HASH_TABLE_LOAD_FACTOR)) {
        // TODO
        return HASH_TABLE_STATUS_FULL;
    }

    // create new node
    struct hash_table_node *new_node = malloc(sizeof(struct hash_table_node));
    if (new_node == NULL) {
        return HASH_TABLE_STATUS_OUT_OF_MEMORY;
    }
    new_node->key = key;
    new_node->value = value;
    new_node->ptr_next = NULL;

    // hash node's key and modulo it by size to get number in range [0, size)
    unsigned long index = hash_string(key) % map->size;

    struct hash_table_node *node = map->array[index];

    // if this spot in the hashtable has not yet been assigned, assign it and return success
    if (node == NULL) {
        map->array[index] = new_node;
        return HASH_TABLE_STATUS_SUCCESS;
    }

    while (node->ptr_next != NULL) {
        node = node->ptr_next;
    }

    node->ptr_next = new_node;
    return HASH_TABLE_STATUS_SUCCESS;
}

// hash_table_remove removes the value of the given key.
// it will return NOT_FOUND if the key could not be found
enum hash_table_status
hash_table_remove(struct hash_table *map, const char *key) {
    // hash key
    unsigned long index = hash_string(key) % map->size;

    // get the key at that index
    struct hash_table_node *array = map->array;
    if (array == NULL) {
        return HASH_TABLE_STATUS_NOT_FOUND;
    }
    struct hash_table_node *entry = &array[index];
    if (entry == NULL) {
        return HASH_TABLE_STATUS_NOT_FOUND;
    }

    //todo: improve when we've changed the implementation
    //if this is the only entry, we set the memory back to 0 
    if (strcmp(entry->key, key) == 0) {
        memset(entry, 0, sizeof(struct hash_table_node));
        return HASH_TABLE_STATUS_SUCCESS;
    }

    // if the key at the entry does not match the given key, we skip to the next hash_table_node in the linked list
    struct hash_table_node *prev_entry = NULL;
    while (strcmp(entry->key, key) != 0) {
        if (entry->ptr_next == NULL) {
            // if there is no next element, we return an error
            return HASH_TABLE_STATUS_NOT_FOUND;
        }
        prev_entry = entry;
        entry = entry->ptr_next;
    }

    // if there was a previous el
    if (prev_entry != NULL) {
        // and there is a next el, we connect the two
        if (entry->ptr_next != NULL) {
            prev_entry->ptr_next = entry->ptr_next;
        } else {
        // and there is no next el, we free the prev el's ptr_next
            prev_entry->ptr_next = NULL;
        }
    }

    // delete the entry
    free(entry);
    return HASH_TABLE_STATUS_SUCCESS;
}
