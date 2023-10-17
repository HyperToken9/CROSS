
#include "node.h"


void init_node(struct NodeHandle *nh, char name[])
{
    printf("Method Currently Does Nothing\n");

    nh->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    nh->address.sin_family = AF_INET;
    nh->address.sin_addr.s_addr = inet_addr("127.0.0.1");
    nh->address.sin_port = htons(80808);
    

    int result = connect(nh->socket_descriptor, 
                        (struct sockaddr*)&nh->address, 
                        len(nh->address));

    if (result == -1)
    {
        printf("Failed To Connect To CROSS Core\n");
        exit(0);
    }

    write(nh->socket_descriptor, , );

}