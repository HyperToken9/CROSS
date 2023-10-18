
#include<stdio.h>

#include "cross/node/node.h"

int main(int argc, char* argv[])
{
    printf("You have entered %d arguments:\n", argc);

    if (argc < 2)
     {
        printf("2 Failed\n");
        return 0;
     }   

    struct NodeHandle nh;

    init_node(&nh, argv[1]);

    return 0;
}
