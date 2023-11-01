#include <stdio.h>
#include <stdlib.h>

#include "node.h"

void linkedlist_append(LinkedListNode ** headptr, void * data);

void * linkedlist_find(LinkedListNode * head, void * data , int (*comparator)(void *, void * ));

void linkedlist_print(LinkedListNode * head, void (*print)(void *));

