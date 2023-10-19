#pragma once

#include <netinet/in.h>

struct NodeHandle{

    /* Networking */
    int socket_descriptor;
    struct sockaddr_in address;

    /*Node Details*/
    int is_registered;
    char node_name[50];

};

typedef struct NodeHandle NodeHandle;