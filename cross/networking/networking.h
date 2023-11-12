
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>


struct sockaddr_in networking_address_init(char ip_address[], int port_no);

int networking_socket_init(struct sockaddr_in address);

// void networking_port_listen();

void networking_write_message(int socket_descriptor, void * message, unsigned int message_size);

// void networking_read_message(int socket_descriptor, void * message, unsigned int message_size);

