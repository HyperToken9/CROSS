#pragma once

#include "topic_list.h"

struct NodeList
{
    
    char node_name[50];

    struct TopicList *topics;
    
    struct NodeList* next;
};