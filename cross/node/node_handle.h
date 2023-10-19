#pragma once

#include <netinet/in.h>

struct Subscription{
    
    struct Subscription * next;
};

typedef struct Subscription Subscription;

struct Publication{
    
    struct Publication * next;
};

typedef struct Publication Publication;


struct NodeHandle{

    /* Networking with Master*/
    int socket_descriptor;
    struct sockaddr_in address;

    /*Node Details*/
    int is_registered;
    char node_name[50];

    Subscription * subscriptions;
    Publication * publications;
};

typedef struct NodeHandle NodeHandle;