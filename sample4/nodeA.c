
#include<stdio.h>

#include "cross/node/node.h"
#include "cross/publisher/publisher.h"
#include "cross/subscriber/subscriber.h"


void callback(void * data, unsigned int data_size)
{   
    char * string = (char *)data; 
    printf("\nB says:  %s\n", string);
}

int main(int argc, char* argv[])
{
    NodeHandle nh;
    Publisher string_publisher;
    Subscriber string_subscriber;
    char string[100];

    node_init(&nh, "NodeA");

    subscriber_init(&string_subscriber, &nh, "B_talks", callback);
    publisher_init(&string_publisher, &nh, "A_talks");

    while(1)
    {
        printf("Enter a Message: ");
        fgets(string, sizeof(string), stdin);

        publisher_publish(&string_publisher, &nh, string, sizeof(string));
    }


    return 0;
}