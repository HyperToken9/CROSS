#pragma once

#include <netinet/in.h>
#include <pthread.h> 

#include "master_registry.h"
#include "master_node_connection.h"

struct Master{

    int socket_descriptor;
    
    struct sockaddr_in address;

    // Incoming Node
    pthread_mutex_t incoming_node_lock;
    struct MasterNodeConnection incoming_node;

    // Shareable Data
    pthread_mutex_t registry_lock;
    struct MasterRegistry registry;

};

