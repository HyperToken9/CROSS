#pragma once

struct Master{
    
    int listen_sd, connect_sd;
    
    struct sockaddr_in address;

    // Incoming Node
    int node_size;
    struct sockaddr_in node_address;
};

