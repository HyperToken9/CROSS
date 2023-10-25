
#include "node.h"


void node_init(NodeHandle *nh, char name[])
{
    /* Catch Errors */
    // if (nh->is_registered) 
    // {
    //     printf("Node Can Only Be Initialized Once\n");
    //     exit(0);
    // }

    if ( strcmp(name, "") == 0 ) 
    {
        printf("Node Needs A Valid Name\n");
        exit(0);
    }

    // Create Node Thread

    // Set Up a socket where Other Nodes Message the Node
    nh->reading_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    nh->reading_address.sin_family = AF_INET;
    nh->reading_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    nh->reading_address.sin_port = 0; // Random Assignment

    bind(nh->reading_socket_descriptor, 
        (struct sockaddr *)& nh->reading_address,
        sizeof(nh->reading_address));
    listen(nh->reading_socket_descriptor, 10);

    // Use getsockname to retrieve the actual port number
    socklen_t addr_len = sizeof(nh->reading_address);
    getsockname(nh->reading_socket_descriptor, (struct sockaddr *)&nh->reading_address, &addr_len);

    // Display the assigned port number
    printf("Assigned Port Number: %d\n", ntohs(nh->reading_address.sin_port));

    // Initialize Mutex to Ensure only a singular thread is accessing node handle

    strcpy(nh->node_name, name);
    
    
    node_connect_to_master(nh);

    /* Create Message */
    NodeToMasterMessage message;
    message.type = INIT_NODE;
    strcpy(message.node_name, name);
    message.node_address = nh->reading_address;

    node_message_master(nh, message);

    node_disconnect_from_master(nh);

    nh->is_registered = 1;
    
}


void node_connect_to_master(NodeHandle *nh)
{
    nh->writing_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (nh->writing_socket_descriptor < 0)
    {
        printf("\n Socket creation error \n"); 
        exit(EXIT_FAILURE); 
    }

    nh->writing_address.sin_family = AF_INET;
    nh->writing_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    nh->writing_address.sin_port = htons((uint16_t)8080);
    

    int result = connect(nh->writing_socket_descriptor, 
                        (struct sockaddr*)&nh->writing_address, 
                        sizeof(nh->writing_address));

    if (result == -1)
    {
        printf("Failed To Connect To CROSS Core\n");
        exit(0);
    }
}

void node_message_master(NodeHandle *nh, NodeToMasterMessage message)
{
    int result = write(nh->writing_socket_descriptor,
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
    close(nh->writing_socket_descriptor);
}
