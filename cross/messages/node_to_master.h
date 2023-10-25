#pragma once

#include <netinet/in.h>

#include "types.h"

struct NodeToMasterMessage 
{

    char node_name[50];
    enum NodeToMasterMessageType type;
    struct sockaddr_in node_address;

    char topic_name[50];
    enum CROS_MessageTypes topic_type;

}__attribute__((packed));

typedef struct NodeToMasterMessage NodeToMasterMessage;