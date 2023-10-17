#pragma once

#include "../types/node.h"

struct MasterMessage 
{
    char node_name[50];
    enum NodeType node_type;
};