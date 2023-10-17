
#include "master.h"

void master_init(struct Master *master, int port_no)
{

    master->listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    master->address.sin_family = AF_INET;
    master->address.sin_addr.s_addr = inet_addr("127.0.0.1");
    master->address.sin_port = htons(port_no);
    
    bind(master->listen_sd, (struct sockaddr*)&master->address, sizeof(master->address));

    listen(master->listen_sd, 5);

    // master_address.sin_family = AF_INET;
    // master_address.

    printf("Master Listening At Port %d\n", port_no);
}

void master_listen(struct Master *master)
{
    master->node_size = sizeof(master->node_size);

    master->connect_sd = accept(master->listen_sd, 
        (struct sockaddr*)& master->node_address, &master->node_size);
}

void master_process_incoming_connection(struct Master *master)
{
    // Listens to incomming node
    // Takes details from node
    //   - Node Name
    //   - Subscriber / Publisher
    //   - Topic Name
    //   - Data Type

    struct MasterMessage message;
    int flag = read(master->connect_sd, &message, sizeof(message));

    print_master_message(message);

    
    exit(0);

}

void master_close_connection(struct Master *master)
{
    close(master->connect_sd);
}

void master_close(struct Master *master)
{

    printf("Master Shutting Down\n");
}

 