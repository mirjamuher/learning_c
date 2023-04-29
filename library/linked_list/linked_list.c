#include "linked_list.h"
#include <assert.h>
#include <stdlib.h>

// Given a linked list, count how many nodes there are.
unsigned int 
linked_list_size(struct linked_list_node *list) {
    unsigned int ctr = 0;
    while (list != NULL) {
        ctr++;
        list = list->ptr_nxt;
    }
    // alternative approach:
    // for ( ; list != NULL; list = list->ptr_nxt) {
    //     ctr++;
    // }
    return ctr;
}

// Given a linked list, free up all of the nodes.
void 
linked_list_destroy(struct linked_list_node *list) {
    struct linked_list_node *nxt = list;

    while (nxt != NULL) {
        list = nxt;
        nxt = nxt->ptr_nxt;
        free(list);
    }
}

// Construct a new linked list node, given the data of the node, and prepend it.
enum linked_list_status
linked_list_prepend(const void *data, struct linked_list_node **list) {
    // allocate memory for a new linked_list_node
    struct linked_list_node *new_node = malloc(sizeof(struct linked_list_node));
    if (new_node == NULL) {
        return LINKED_LIST_STATUS_OUT_OF_MEMORY;
    };

    new_node->data = data;
    new_node->ptr_nxt = *list;

    // make `new` the new header being pointed to
    *list = new_node;

    return LINKED_LIST_STATUS_SUCCESS;
}

// Construct a new linked list node, give the data of the node and append it.
enum linked_list_status
linked_list_append(const void *data, struct linked_list_node **list) {
    // step 1: malloc & create new node
    struct linked_list_node *new_node = malloc(sizeof(struct linked_list_node));
    if(new_node == NULL) {
        return LINKED_LIST_STATUS_OUT_OF_MEMORY;
    };
    new_node->data = data;
    new_node->ptr_nxt = NULL;

    // step 2: find last entry & update it's ptr_next
    struct linked_list_node *n = *list;
    if (n != NULL) {
        while (n->ptr_nxt != NULL) {
            n = n->ptr_nxt;
        }
        n->ptr_nxt = new_node;
    } else {
        *list = new_node;
    }

    return LINKED_LIST_STATUS_SUCCESS;
}

// Given the head of the list, destroy the given data node and return the head of the list
// if no data was found, do nothing
enum linked_list_status
linked_list_delete_element(const void *data, struct linked_list_node **header) {
    // crnt_node holds the crnt_node's ptr
    struct linked_list_node *crnt_node = *header;
    // matched_node holds the ptr to the node with matching data
    struct linked_list_node *matched_node = NULL;
    // prev_node holds the ptr to the node pointing to our matched_node
    struct linked_list_node *prev_node = NULL;

    // loop through list until we find matching data
    while (crnt_node != NULL) {
        const void *crnt_data = crnt_node->data;
        if (data == crnt_data) {
            matched_node = crnt_node;
            break;
        }
        prev_node = crnt_node;
        crnt_node = crnt_node->ptr_nxt;
    }

    // if no match was found, return the given head
    if (matched_node == NULL) {
        return LINKED_LIST_STATUS_NOT_FOUND;
    }

    // if a match was found
    struct linked_list_node *new_header = NULL;
    // (a) if there is no prev_node (because matched_node = header) then we return the ptr_next as the header
    if (prev_node == NULL) {
        new_header = matched_node->ptr_nxt;
    } 
    // (b) if there is no ptr_next because we're at the end of this list, delete the ptr_next of the prev item and return header
    // (c) if we're in the middle of the list, connect prev_node's ptr_next to the node after matched_node
    else {
        prev_node->ptr_nxt = matched_node->ptr_nxt;;
        new_header = *header;
    }

    // step 3: free memory
    free(matched_node);

    // step 4: update where header is pointing to
    *header = new_header;

    return LINKED_LIST_STATUS_SUCCESS;
}
