#pragma once

#include <netinet/in.h>

struct MasterNodeConnection{
    
    int socket_descriptor, node_size;
    struct sockaddr_in node_address;

};