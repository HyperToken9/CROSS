
#include<stdio.h>

#include "cross/node/node.h"


int main()
{
    printf("Hello World\n");

    struct NodeHandle nh;

    init_node(&nh, "sample-publisher");

    return 0;
}