
#include <stdio.h>

#include "cross/node/node.h"
#include "cross/publisher/publisher.h"

int main(int argc, char* argv[])
{

    NodeHandle nh;
    Publisher int_publisher;
    int data;

    node_init(&nh, "NodeA");

    publisher_init(&int_publisher, &nh, "integer1");


    while(1)
    {   
        printf("Enter Integer: ");
        scanf("%d", &data);

        publisher_publish(&int_publisher, &nh, &data, sizeof(data));
    }
     
    return 0;
}
