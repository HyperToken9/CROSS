
#include<stdio.h>

#include "cross/node/node.h"
#include "cross/publisher/publisher.h"
#include "cross/subscriber/subscriber.h"

void callback(void * data, unsigned int data_size)
{   
    char * string = (char *)data; 
    printf("Message Recieved:  %s\n", string);

}

int main(int argc, char* argv[])
{

    NodeHandle nh, nh1;
    Publisher string_publisher;
    Subscriber int_subscriber;

    node_init(&nh, "listener");

    subscriber_init(&int_subscriber, &nh, "chatter", callback);

    // Dont Quit
    while(1);


    return 0;
}