#pragma once

// #include "../types/node.h"
#include "types.h"

struct NodeToMasterMessage 
{
    char node_name[50];
    char topic_name[50];
    enum NodeToMasterMessageType type;

}__attribute__((packed));

typedef struct NodeToMasterMessage NodeToMasterMessage;