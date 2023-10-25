#pragma once

#include <pthread.h> 
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

    /* Node Thread */ 
    pthread_t listen_thread;
    // pthread_mutex_t handle_lock;
    
    /* Networking : Miscellaneous to Node */ 
    int reading_socket_descriptor;
    struct sockaddr_in reading_address;


    /* Networking : Node to Master*/
    int writing_socket_descriptor;
    struct sockaddr_in writing_address;

    /*Node Details*/
    int is_registered;
    char node_name[50];

    Subscription * subscriptions;
    Publication * publications;
};
typedef struct NodeHandle NodeHandle;
