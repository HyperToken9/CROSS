#pragma once

#include "../types/node.h"

struct MasterMessage 
{
    char node_name[50];
    int id;
    enum NodeType node_type;
}__attribute__((packed));