
#include "master.h"

#define PORT_NO 80808

void master_init(struct Master *master)
{

    master->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    master->address.sin_family = AF_INET;
    master->address.sin_addr.s_addr = inet_addr("127.0.0.1");
    master->address.sin_port = htons((uint16_t)PORT_NO);
    
    bind(master->socket_descriptor, (struct sockaddr*)&master->address, sizeof(master->address));

    listen(master->socket_descriptor, 5);

    
    /* Initialize Mutex Locks */
    if (pthread_mutex_init(&master->registry_lock, NULL) != 0) { 
        printf("\n Registry Lock Failed\n"); 
        exit(EXIT_FAILURE);
    } 
    if (pthread_mutex_init(&master->incoming_node_lock, NULL) != 0) { 
        printf("\n Socket Node Lock Failed\n"); 
        exit(EXIT_FAILURE);
    } 


    // pthread_mutex_unlock(&master->registry_lock); 

    printf("Master Listening At Port %d\n", PORT_NO);
}

void master_listen(struct Master *master)
{
   
    pthread_mutex_lock(&master->incoming_node_lock);

    // printf("Access Acquired\n");
    // master->incoming_node.node_size = sizeof(master->incoming_node.node_size);
    
    master->incoming_node.socket_descriptor = accept(master->socket_descriptor, 
                                                    (struct sockaddr*)& master->incoming_node.node_address, 
                                                    &master->incoming_node.node_size);

    // printf("Access Dissmissed\n");

    pthread_mutex_unlock(&master->incoming_node_lock);
    
}

/*
    Runs parallely to extablish a connection with incoming nodes
*/
void* master_process_incoming_connection(void * arg)
{
    // Listens to incomming node
    // Takes details from node
    //   - Node Name
    //   - Subscriber / Publisher
    //   - Topic Name
    //   - Data Type
    // pthread_detach(pthread_self());

    /* Recieve Arguments */
    struct Master * master = (struct Master *) arg; 
    /* / / / / / / / / */

    /* Duplicate Socket Conenctiom */
    pthread_mutex_lock(&master->incoming_node_lock);

    struct MasterNodeConnection node_socket;

    node_socket = master->incoming_node;

    // close(master->incoming_node.socket_descriptor);

    pthread_mutex_unlock(&master->incoming_node_lock);

    master = NULL;
    /* / / / / / / / / / / / / / / */


    /* Try to handle incoming node */
    struct MasterMessage message;
    // char buffer[2048];
    int flag;
    
    flag = read(node_socket.socket_descriptor, 
                // buffer, 2048);
                &message, sizeof(struct MasterMessage));

    if (flag < 0)
        perror("Error receiving data");
    else
        printf("Revied");

    // printf("Rec: %s\n", buffer);
    print_master_message(message);

    // sleep(5);

    printf("Exiting THread\n");
    close(node_socket.socket_descriptor);
    // sleep(2);
    // pthread_exit(NULL);

}

void master_close_connection(struct Master *master)
{
    printf("Master_CloseConnection Does Nothing\n");
    // close(master->connect_sd);
}

void master_close(struct Master *master)
{

    printf("Master Shutting Down\n");
}

 