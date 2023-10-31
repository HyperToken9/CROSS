#pragma once

#include <pthread.h> 
#include <netinet/in.h>

#include "../linkedlist/linkedlist.h"

struct NodePort{
    struct sockaddr_in address;

    // struct NodePort * next;

};
typedef struct NodePort NodePort;


struct Subscription{
    char topic_name[50];
    // struct Subscription * next;
};
typedef struct Subscription Subscription;


struct Publication{
    
    char topic_name[50];

    /* List of Node Ports */
    LinkedListNode * subscribed_nodes;
    // NodePort * subscribed_nodes;

    // struct Publication * next;
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

    /* List of Publication */
    LinkedListNode * subscriptions;
    // Subscription * subscriptions;

    /* List of Subscription */
    LinkedListNode * publications;
    // Publication * publications;

};
typedef struct NodeHandle NodeHandle;
