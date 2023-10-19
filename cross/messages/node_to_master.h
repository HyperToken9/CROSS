#pragma once

// #include "../types/node.h"
#include "types.h"

struct NodeToMasterMessage 
{
    char node_name[50];
    // int id;
    enum MessageType type;

}__attribute__((packed));