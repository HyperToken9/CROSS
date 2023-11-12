
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

    publisher_init(&string_publisher, &nh, "chatter", CROS_MSG_TYPE_STRING);
    // publisher_init(&string_publisher, &nh, "chatter2", CROS_MSG_TYPE_STRING);
    // publisher_init(&string_publisher, &nh1, "hup1", CROS_MSG_TYPE_STRING);
    
    // subscriber_init(&int_subscriber, &nh, "listen1", CROS_MSG_TYPE_INT);
    // subscriber_init(&int_subscriber, &nh1, "hup2", CROS_MSG_TYPE_INT);
    // printf("Passed Through");
    sleep(3);

    strcpy(data, "Hello Subscribers");

    publisher_publish(&string_publisher, &nh, data, sizeof(data));
    // Dont Quit
    while(1);


    return 0;
}
