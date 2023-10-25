#pragma once

#include "topic_list.h"

struct NodeList
{
    char name[50];

    struct sockaddr_in address;
    
    /*
        List Of Topics This Node 
        Subscribes or Publishes To
    */
    struct TopicList *topics;

    /* Pointer to next Node in List*/
    struct NodeList* next;
};