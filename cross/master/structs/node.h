#pragma once

#include <netinet/in.h>

#include "topic.h"
#include "../../linkedlist/linkedlist.h"


struct Node
{
    char name[50];

    struct sockaddr_in address;
    
    /*
        List Of Topics This Node 
        Subscribes or Publishes To
    */
    LinkedListNode * topics;
    // struct TopicList *topics;

    /* Pointer to next Node in List*/
    // struct NodeList* next;
};