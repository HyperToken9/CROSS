#include<stdio.h>

#include "cross/node/node.h"
#include "cross/subscriber/subscriber.h"


void callback(void * data, unsigned int data_size)
{   
    int * integer = (int *)data; 
    printf("Int Recieved:  %d\n", *integer);

}

int main(int argc, char* argv[])
{
    NodeHandle nh;
    Subscriber int_subscriber;

    node_init(&nh, "NodeC");

    subscriber_init(&int_subscriber, &nh, "integer2", callback);

    // Dont Quit
    while(1);


    return 0;
}