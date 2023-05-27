#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
        map->el_num += 1;
        return HASH_TABLE_STATUS_SUCCESS;
    }

    // if it's not empty, we keep  moving down the list of pointers until we find an empty spot
    while (node->ptr_next != NULL) {
        node = node->ptr_next;
    }

    node->ptr_next = new_node;
    map->el_num += 1;
    return HASH_TABLE_STATUS_SUCCESS;
}

// hash_table_remove removes the value of the given key.
// it will return NOT_FOUND if the key could not be found
enum hash_table_status
hash_table_remove(struct hash_table *map, const char *key) {
    // hash key
    unsigned long index = hash_string(key) % map->size;

    // get the node at that index
    struct hash_table_node *node = map->array[index];
    if (node == NULL) {
        return HASH_TABLE_STATUS_NOT_FOUND;
    }

    // if key at first entry matches
    if (strcmp(node->key, key) == 0) {
        // if there are more nodes, we have to set this bit in the array to the ptr_next
        map->array[index] = node->ptr_next;
        free(node);
        map->el_num -= 1;
        return HASH_TABLE_STATUS_SUCCESS;
    }

    // otherwise keep looping until you find the entry
    while (node->ptr_next != NULL) {
        struct hash_table_node *nxt_node = node->ptr_next;
        // if the next node has a matching key, we delete it and stick crnt node and nxt_nxt_node together
        if (strcmp(nxt_node->key, key) == 0) {
            node->ptr_next = nxt_node->ptr_next;
            free(nxt_node);
            map->el_num -= 1;
            return HASH_TABLE_STATUS_SUCCESS;
        }
        node = node->ptr_next;
    }

    // if we've made it here, the key doesn't exist in the map
    return HASH_TABLE_STATUS_NOT_FOUND;
}

void
hash_table_print(const struct hash_table *map, void (*value_printer)(const void *)) {
    for (int i = 0; i < map->size; i++) {
        struct hash_table_node *node = map->array[i];
        if (node != NULL) {
            printf("%s: ",node->key);
            value_printer(node->value);
            printf("\n");

            while (node->ptr_next != NULL) {
                struct hash_table_node *nxt_node = map->array[i]->ptr_next;
                printf("%s: ", nxt_node->key);
                value_printer(nxt_node->value);
                printf("\n");   
                node = nxt_node;
            }
        }
    }
}
