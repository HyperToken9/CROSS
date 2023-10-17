#include "print.h"

void print_master_message(struct MasterMessage message)
{
    printf("-- Master Message --\n");
    
    printf("\tNode Name: %s\n\t", message.node_name);

    //TODO: print_node_type(message.node_name);
    if (message.node_type)
        printf("Node Type: Publisher\n");
    else
        printf("Node Type: Subscriber\n");

    printf("-------------------\n");

}