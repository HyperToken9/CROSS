#include "linkedlist.h"


void linkedlist_append(LinkedListNode ** headptr, void * data)
{
    LinkedListNode * new_node = (LinkedListNode *) calloc(sizeof(LinkedListNode), 1), * temp;
    new_node->data = data;

    if(*headptr == NULL)
    {
        *headptr = new_node;
        return;
    }

    temp = *headptr;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new_node;

}

void * linkedlist_find(LinkedListNode * head, void * data ,int (*comparator)(void *, void * ))
{
    LinkedListNode * temp = head;

    while (temp)
    {
        if ( comparator( temp->data, data ) )
            return temp->data;
            
        temp = temp->next;
    }

    return NULL;
}

void linkedlist_print(LinkedListNode * head, void (*print)(void *))
{
    LinkedListNode * temp = head;

    while (temp)
    {
        print(temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int linkedlist_length(LinkedListNode * head)
{
    LinkedListNode * traversal = head;
    int length = 0;

    while ( traversal != NULL )
    {
        length++;
        traversal = traversal->next;
    }

    return length;

}

