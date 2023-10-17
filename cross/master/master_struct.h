#pragma once

#include <netinet/in.h>

#include "master_registry.h"

struct Master{

    int listen_sd, connect_sd;
    
    struct sockaddr_in address;

    // Incoming Node
    int node_size;
    struct sockaddr_in node_address;

    // Shareable Data
    struct MasterRegistry registry;

};

