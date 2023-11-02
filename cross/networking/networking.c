
#include "networking.h"

struct sockaddr_in networking_address_init(char ip_address[], int port_no)
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address);
    address.sin_port = htons((uint16_t)port_no);

    return address;

}

// void networking_socket_init(){}

// void networking_port_listen(){}

