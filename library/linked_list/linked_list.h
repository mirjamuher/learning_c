#pragma once

struct linked_list_node {
    const void *data;
    struct linked_list_node *ptr_nxt;
};

enum linked_list_status {
    LINKED_LIST_STATUS_SUCCESS = 0,
    LINKED_LIST_STATUS_ERROR = 1,
    LINKED_LIST_STATUS_NOT_FOUND = 2,
    LINKED_LIST_STATUS_OUT_OF_MEMORY = 3,
    LINKED_LIST_STATUS_INVALID_ARGUMENT = 4,
};

// Construct a new linked list node, given the data of the node and prepend it.
// give a pointer to your list head
enum linked_list_status
linked_list_prepend(const void *data, struct linked_list_node **list);

// Construct a new linked list node, give the data of the node and append it.
// give a pointer to your list head
enum linked_list_status
linked_list_append(const void *data, struct linked_list_node **list);

// Given a linked list, count how many nodes there are.
unsigned int 
linked_list_size(struct linked_list_node *list);

// Given a linked list, free up all of the nodes.
void 
linked_list_destroy(struct linked_list_node *list);

// Given the head of the list, destroy the given data node and return the head of the list
// if no data was found, do nothing
// give a pointer to your list head
enum linked_list_status
linked_list_delete_element(const void *data, struct linked_list_node **header);
