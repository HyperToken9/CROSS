#pragma once

#include <pthread.h> 
#include <netinet/in.h>

struct NodePort{
    struct sockaddr_in address;
    struct NodePort * next;
};
typedef struct NodePort NodePort;


struct Subscription{
    char topic_name[50];
    struct Subscription * next;
};
typedef struct Subscription Subscription;


struct Publication{
    
    char topic_name[50];
    NodePort * subscribed_nodes;

    struct Publication * next;
};
typedef struct Publication Publication;


struct NodeHandle{

    /* Node Thread */ 
    pthread_t reading_thread;
    
    /* Networking : Miscellaneous to Node */ 
    int reading_socket_descriptor;
    struct sockaddr_in reading_address;


    /* Networking : Node to Master*/
    int writing_socket_descriptor;
    struct sockaddr_in writing_address;

    /*Node Details*/
    int is_registered;
    char node_name[50];

    pthread_mutex_t registry_lock;
    Subscription * subscriptions;
    Publication * publications;
};
typedef struct NodeHandle NodeHandle;
