
#include "master.h"

#define PORT_NO 80808

void master_init(struct Master *master)
{

    master->listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    master->address.sin_family = AF_INET;
    master->address.sin_addr.s_addr = inet_addr("127.0.0.1");
    master->address.sin_port = htons((uint16_t)PORT_NO);
    
    bind(master->listen_sd, (struct sockaddr*)&master->address, sizeof(master->address));

    listen(master->listen_sd, 5);

    pthread_mutex_unlock(&master->registry.lock); 

    printf("Master Listening At Port %d\n", PORT_NO);
}

void master_listen(struct Master *master)
{
    master->node_size = sizeof(master->node_size);

    master->connect_sd = accept(master->listen_sd, 
        (struct sockaddr*)& master->node_address, &master->node_size);
}

void* master_process_incoming_connection(void * arg)
{
    // Listens to incomming node
    // Takes details from node
    //   - Node Name
    //   - Subscriber / Publisher
    //   - Topic Name
    //   - Data Type
    // pthread_detach(pthread_self());

    struct Master * master = (struct Master *) arg; 

    struct MasterMessage message;
    int flag = read(master->connect_sd, &message, sizeof(message));

    print_master_message(message);

    // sleep(5);

    printf("Exiting THread");

    sleep(2);
    pthread_exit(NULL);

}

void master_close_connection(struct Master *master)
{
    close(master->connect_sd);
}

void master_close(struct Master *master)
{

    printf("Master Shutting Down\n");
}

 