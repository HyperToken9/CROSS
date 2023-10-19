
#include<stdio.h>

#include "cross/node/node.h"
#include "cross/publisher/publisher.h"

int main(int argc, char* argv[])
{

    NodeHandle nh;
    Publisher string_publisher;

    node_init(&nh, "talker");

    publisher_init(&string_publisher, &nh,
                    "chatter", CROS_MSG_TYPE_STRING);

    // printf("Passed Through");

    return 0;
}
