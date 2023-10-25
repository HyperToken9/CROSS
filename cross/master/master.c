
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
    sleep(2); // Comment out when not testing
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
    NodeToMasterMessage message;
    int flag;
    
    flag = read(node_socket.socket_descriptor, 
                &message, sizeof(NodeToMasterMessage));

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


void master_process_message(struct Master *master, NodeToMasterMessage message)
{
    struct NodeList *node_trav_ptr, * new_node;
    struct TopicList *topic_trav_ptr, *new_topic;
    
    pthread_mutex_lock(&master->registry_lock);
    if (message.type == INIT_NODE)
    {   
        /* Initialize New Node */
        new_node = (struct NodeList*)calloc(sizeof(struct NodeList), 1);
        strcpy(new_node->name, message.node_name);
        new_node->address = message.node_address;
        // new_node->topics = NULL;
        // new_node->next = NULL;

        /* Add to List */
        node_trav_ptr = master->registry.active_nodes;
        if (node_trav_ptr == NULL)
        {
            master->registry.active_nodes = new_node;
        }
        else
        {
            while (node_trav_ptr->next != NULL)
            {
                printf("Comparing: %s with %s\n", node_trav_ptr->name, new_node->name);
                if (strcmp(node_trav_ptr->name, new_node->name) == 0)
                {
                    printf("Node with name {%s} already exists\n", 
                            new_node->name);
                    pthread_mutex_unlock(&master->registry_lock);
                    return;
                }

                node_trav_ptr = node_trav_ptr->next;
            } 
            
            printf("Comparing: %s with %s\n", node_trav_ptr->name, new_node->name);
            if (strcmp(node_trav_ptr->name, new_node->name) == 0)
            {
                printf("Node with name {%s} already exists\n", 
                        new_node->name);
                pthread_mutex_unlock(&master->registry_lock);
                return;
            }


            node_trav_ptr->next = new_node;
        } 
        

    }
    else if ((message.type == NEW_PUBLISHER) 
          || (message.type == NEW_SUBSCRIBER))
    {
        /*  We recieve 
         *     - node name
         *     - topic name
         *     - topic type
         1. Need to fine the node to attach the topic to
            i. We assume the node is in the list
         2. Add Node to topic list
         MAIN: Desiging and setting up a peer to peer connection between nodes
         3. Inform all the future nodes subscribed to that topic to listen to a port
         4. Inform all the prexisting nodes about the new port
         */ 
        
        // 1. 
        node_trav_ptr = master->registry.active_nodes;

        while (strcmp(node_trav_ptr->name, message.node_name) != 0)
            node_trav_ptr = node_trav_ptr->next; 
        
        // 2.
        // ! Need to check topic type conflicts

        new_topic = (struct TopicList*)calloc(sizeof(struct TopicList), 1);
        strcpy(new_topic->topic_name, message.topic_name); 
        new_topic->message_type = message.topic_type;
        if (message.type == NEW_PUBLISHER)
            new_topic->type = PUBLISHER;
        else 
            new_topic->type = SUBSCRIBER; 

        if (node_trav_ptr->topics == NULL)
            node_trav_ptr->topics = new_topic;
        else
        {
            topic_trav_ptr = node_trav_ptr->topics;

            while (topic_trav_ptr->next)
                topic_trav_ptr = topic_trav_ptr->next;
            
            topic_trav_ptr->next = new_topic;

        }
        
    }
    else
        printf("This Message Type is not supported by cros YET\n");
    
    pthread_mutex_unlock(&master->registry_lock);

}

void master_print_registry(struct Master *master)
{   
    printf("~~ Master Registry ~~\n");
    
    for (struct NodeList * node = master->registry.active_nodes; node != NULL; node = node->next)
    {
        printf("Node { %s } At Port (%d):", node->name, ntohs(node->address.sin_port));

        for(struct TopicList * topic = node->topics; topic != NULL; topic = topic->next)
        {
            printf(" %s ( %s ) | ", topic->topic_name, topic->type == SUBSCRIBER ? "SUB": "PUB");
        } 

        printf("\n");

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

 