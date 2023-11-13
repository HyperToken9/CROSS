
#include<stdio.h>

#include "cross/node/node.h"
#include "cross/publisher/publisher.h"
#include "cross/subscriber/subscriber.h"

NodeHandle nh;
Publisher int_publisher;
Subscriber int_subscriber;

void callback(void * data, unsigned int data_size)
{   
    int * integer = (int *)data; 
    printf("Int Recieved:  %d\n", integer);

    /* Doubled in Value */ 
    *(integer) *= 2;

    publisher_publish(&int_publisher, &nh, integer, data_size);

}

int main(int argc, char* argv[])
{

    node_init(&nh, "NodeB");

    subscriber_init(&int_subscriber, &nh, "integer1", callback);
    publisher_init(&int_publisher, &nh, "integer2");

    // Dont Quit
    while(1);


    return 0;
}