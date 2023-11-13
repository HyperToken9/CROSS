#include "print.h"

void print_master_message(NodeToMasterMessage message)
{
    printf("-- Master Message --\n");
    
    printf("\tNode Name: %s\n", message.node_name);

    //TODO: print_node_type(message.node_name);
    printf("\tMessage Type: ");

    if (message.type == INIT_NODE)
        printf("Node Initialization");
    else if (message.type == NEW_SUBSCRIBER)
        printf("New Subcriber");
    else if (message.type == NEW_PUBLISHER)
    {
        printf("New Publisher");
        printf("(Topic Name:  %s)", message.topic_name);
    }    
    else
        printf("Unknown Message Type");
    printf("\n");


    printf("-------------------\n");

}