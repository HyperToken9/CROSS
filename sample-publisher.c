
#include<stdio.h>

#include "cross/node/node.h"

int main(int argc, char* argv[])
{

    struct NodeHandle nh;
    struct Publisher string_publisher;

    node_init(&nh, "talker");

    publisher_init(&string_publisher, 
                    "chatter", CROS_MSG_TYPE_STRING);

    return 0;
}
