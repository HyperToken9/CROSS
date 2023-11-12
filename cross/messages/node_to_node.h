#pragma once

#include <netinet/in.h>

struct NodeToNodeMessage{
    
    int from_master;
    char topic_name[50];

    /* For Master */
    struct sockaddr_in address;

    /* For Subscrber*/
   
}__attribute__((packed));;
typedef struct NodeToNodeMessage NodeToNodeMessage;