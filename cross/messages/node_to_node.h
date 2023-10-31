#pragma once

#include <netinet/in.h>

struct NodeToNodeMessage{
    
    int from_master;
    char topic_name[50];

    struct sockaddr_in address;
    // void data;
};
typedef struct NodeToNodeMessage NodeToNodeMessage;