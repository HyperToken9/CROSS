
#include "master.h"


#define PORT_NO 8080

void master_init(struct Master *master)
{

    /* Setting Up Socket */
    master->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    master->address.sin_family = AF_INET;
    master->address.sin_addr.s_addr = inet_addr("127.0.0.1");
    master->address.sin_port = htons((uint16_t)PORT_NO);

    if (bind(master->socket_descriptor, 
             (struct sockaddr*)&master->address, 
             sizeof(master->address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(master->socket_descriptor, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    /* Initialize Mutex Locks */
    if (pthread_mutex_init(&master->registry_lock, NULL) != 0) { 
        printf("\n Registry Lock Failed\n"); 
        exit(EXIT_FAILURE);
    } 
    if (pthread_mutex_init(&master->incoming_node_lock, NULL) != 0) { 
        printf("\n Socket Node Lock Failed\n"); 
        exit(EXIT_FAILURE);
    } 

    /* Setting Up Registry */
    master->registry.active_nodes = NULL;
    

    printf("Master Listening At Port %d\n", PORT_NO);
}

void master_listen(struct Master *master)
{
   
    

    // printf("Access Acquired\n");
    master->incoming_node.node_size = sizeof(int);
    
    int temp_socket_descriptor = accept(master->socket_descriptor, 
                                        (struct sockaddr*)& master->address, 
                                        &master->incoming_node.node_size);

    if (master->incoming_node.socket_descriptor < 0)
    {
        printf("Accept Failed\n");
        printf("Error Code: %d\n", master->incoming_node.socket_descriptor);
    }   
    pthread_mutex_lock(&master->incoming_node_lock);

    master->incoming_node.in_use = 1;
    master->incoming_node.socket_descriptor = temp_socket_descriptor;
    // printf("Access Dissmissed\n");

    pthread_mutex_unlock(&master->incoming_node_lock);
    
}

void master_wait_thread_initialization(struct Master *master)
{
    sleep(2);
    while (master->incoming_node.in_use);
}
/*
    Runs parallely to extablish a connection with incoming nodes
*/
void* master_process_incoming_connection(void * arg)
{
    // Listens to incomming node
    // Takes details from node
    //   - Node Name
    // pthread_detach(pthread_self());

    /* Recieve Arguments */
    struct Master * master = (struct Master *) arg; 
    /* / / / / / / / / */

    /* Duplicate Socket Conenctiom */
    pthread_mutex_lock(&master->incoming_node_lock);

    struct MasterNodeConnection node_socket;

    node_socket = master->incoming_node;

    master->incoming_node.in_use = 0;
    pthread_mutex_unlock(&master->incoming_node_lock);

    // master = NULL;
    /* / / / / / / / / / / / / / / */


    /* Try to handle incoming node */
    struct NodeToMasterMessage message;
    int flag;
    
    flag = read(node_socket.socket_descriptor, 
                &message, sizeof(struct NodeToMasterMessage));

    if (flag < 0)
        perror("Error receiving data");

    // printf("Rec: %s\n", buffer);
    print_master_message(message);

    /* Process Incomming Data */
    master_process_message(master, message);

    /* Display Updates */
    master_print_registry(master);

    /* Shutting Conenction Down */
    printf("Exiting Thread\n");
    close(node_socket.socket_descriptor);
    pthread_exit(NULL);

}


void master_process_message(struct Master *master, struct NodeToMasterMessage message)
{
    struct NodeList * traveral_ptr, * new_node;
    
    if (message.type == NODE_INIT)
    {   
        printf("Messagge Typing\n");
        /* Initialize New Node */
        new_node = (struct NodeList*)calloc(sizeof(struct NodeList), 1);
        strcpy(new_node->node_name, message.node_name);
        // new_node->topics = NULL;
        // new_node->next = NULL;

        /* Add to List */
        pthread_mutex_lock(&master->registry_lock);
        traveral_ptr = master->registry.active_nodes;
        if (traveral_ptr == NULL)
        {
            master->registry.active_nodes = new_node;
        }
        else
        {
            while (traveral_ptr->next != NULL)
            {
                printf("Comparing: %s with %s\n", traveral_ptr->node_name, new_node->node_name);
                if (strcmp(traveral_ptr->node_name, new_node->node_name) == 0)
                {
                    printf("Node with name {%s} already exists\n", 
                            new_node->node_name);
                    pthread_mutex_unlock(&master->registry_lock);
                    return;
                }

                traveral_ptr = traveral_ptr->next;
            } 
            
            printf("Comparing: %s with %s\n", traveral_ptr->node_name, new_node->node_name);
            if (strcmp(traveral_ptr->node_name, new_node->node_name) == 0)
            {
                printf("Node with name {%s} already exists\n", 
                        new_node->node_name);
                pthread_mutex_unlock(&master->registry_lock);
                return;
            }


            traveral_ptr->next = new_node;
        } 
        pthread_mutex_unlock(&master->registry_lock);

    }
}

void master_print_registry(struct Master *master)
{
    int i = 0;
    
    printf("~~ Master Registry ~~\n");
    
    for (struct NodeList * temp = master->registry.active_nodes; temp != NULL; temp = temp->next)
    {
        printf("Node %d : %s\n", i++, temp->node_name);
    }
    printf("~~ ~~ ~~ ~~ ~~ ~~ ~~");

}


// void master_close_connection(struct Master *master)
// {
//     printf("Master_CloseConnection Does Nothing\n");
//     // close(master->connect_sd);
// }

// void master_close(struct Master *master)
// {

//     printf("Master Shutting Down\n");
// }

 