
#include<stdio.h>

#include "cross/node/node.h"
#include "cross/publisher/publisher.h"
#include "cross/subscriber/subscriber.h"


int main(int argc, char* argv[])
{

    NodeHandle nh;
    Publisher string_publisher;
    Subscriber int_subscriber;
    char data[50];
    
    node_init(&nh, "talker");
    // node_init(&nh1, "walker");

    publisher_init(&string_publisher, &nh, "chatter");

    sleep(3);

    strcpy(data, "Hello Subscribers");

    publisher_publish(&string_publisher, &nh, data, sizeof(data));

    while(1)
     publisher_publish(&string_publisher, &nh, data, sizeof(data));


    return 0;
}
