
#include "node.h"


void node_init(NodeHandle *nh, char name[])
{

    if ( strcmp(name, "") == 0 ) 
    {
        printf("Node Needs A Valid Name\n");
        exit(0);
        return;
    }

    strcpy(nh->node_name, name);

    node_connect_to_master(nh);

    NodeToMasterMessage message;
    strcpy(message.node_name, name);
    message.type = NODE_INIT;

    node_message_master(nh, message);

    node_disconnect_from_master(nh);

    nh->is_registered = 1;
    
}


void node_connect_to_master(NodeHandle *nh)
{
    nh->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (nh->socket_descriptor < 0)
    {
        printf("\n Socket creation error \n"); 
        exit(EXIT_FAILURE); 
    }

    nh->address.sin_family = AF_INET;
    nh->address.sin_addr.s_addr = inet_addr("127.0.0.1");
    nh->address.sin_port = htons((uint16_t)8080);
    

    int result = connect(nh->socket_descriptor, 
                        (struct sockaddr*)&nh->address, 
                        sizeof(nh->address));

    if (result == -1)
    {
        printf("Failed To Connect To CROSS Core\n");
        exit(0);
    }
}

void node_message_master(NodeHandle *nh, NodeToMasterMessage message)
{
    int result = write(nh->socket_descriptor,
                   &message, sizeof(NodeToMasterMessage));

    if (result < 0) 
    {
        perror("Error Writing NodeToMasterMessage\n");
        exit(EXIT_FAILURE);
    }
    // else    
        // printf("Message Succesful\n");
}

void node_disconnect_from_master(NodeHandle *nh)
{
    close(nh->socket_descriptor);
}
