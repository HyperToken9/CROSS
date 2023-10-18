
#include "node.h"


void init_node(struct NodeHandle *nh, char name[])
{
    // printf("Method Currently Does Nothing\n");

    nh->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (nh->socket_descriptor < 0)
    {
        printf("\n Socket creation error \n"); 
        exit(EXIT_FAILURE); 
    }

    nh->address.sin_family = AF_INET;
    nh->address.sin_addr.s_addr = inet_addr("127.0.0.1");
    nh->address.sin_port = htons((uint16_t)80808);
    

    int result = connect(nh->socket_descriptor, 
                        (struct sockaddr*)&nh->address, 
                        sizeof(nh->address));

    if (result == -1)
    {
        printf("Failed To Connect To CROSS Core\n");
        exit(0);
    }

    struct MasterMessage message;
    strcpy(message.node_name, name);
    message.node_type = SUBSCRIBER;
    message.id = 284;
    // char buffer[2048];
    // printf("Enter Message: ");
    // scanf("%s", buffer);
    result = write(nh->socket_descriptor, 
                //    buffer, 2048);
                   &message, sizeof(struct MasterMessage));

    if (result < 0) 
    {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }
    else    
        printf("Message Succesful\n");
    close(nh->socket_descriptor);
}
