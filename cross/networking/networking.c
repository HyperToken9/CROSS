
#include "networking.h"

struct sockaddr_in networking_address_init(char ip_address[], int port_no)
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address);
    address.sin_port = htons((uint16_t)port_no);

    return address;

}

int networking_socket_init(struct sockaddr_in address)
{
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_descriptor < 0)
    {
        printf("\n Socket creation error \n"); 
        exit(EXIT_FAILURE); 
    }

    int result = connect(socket_descriptor, (struct sockaddr*)&address, sizeof(address));

    if (result == -1)
    {
        printf("Failed To Connect\n");
        exit(EXIT_FAILURE);
    }


    return socket_descriptor;

}

void networking_write_message(int socket_descriptor, void * message, unsigned int message_size)
{   
    int result;

    result = write(socket_descriptor, message, message_size);

    if (result < 0)
        perror("Master Error Writing data");
}
// void networking_port_listen(){}

