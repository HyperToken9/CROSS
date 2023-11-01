
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
    master->active_node_registry = NULL;
    

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
    pthread_mutex_lock(&master->registry_lock);
    master_process_message(master, message);
    pthread_mutex_unlock(&master->registry_lock);

    /* Display Updates */
    master_print_registry(master);

    /* Shutting Conenction Down */
    printf("Exiting Thread\n");
    close(node_socket.socket_descriptor);
    pthread_exit(NULL);

}


void master_process_message(struct Master *master, NodeToMasterMessage received_message)
{
    struct Node *new_node, *node_ptr, cmp_node;
    struct Topic *new_topic;
    // printf("Waititng for Unlock\n");
    
    if (received_message.type == INIT_NODE)
    {   
        /* Initialize New Node */
        new_node = (struct Node*)calloc(sizeof(struct Node), 1);
        strcpy(new_node->name, received_message.node_name);
        new_node->address = received_message.node_address;

        /* Add to List */
        if (linkedlist_find(master->active_node_registry, new_node, master_compare_nodes) )
        {
            printf("Node with name {%s} already exists\n", new_node->name);
            return;
        }
        linkedlist_append(&master->active_node_registry, new_node);


    }
    else if ((received_message.type == NEW_PUBLISHER) 
          || (received_message.type == NEW_SUBSCRIBER))
    {
        /*  We recieve 
         *     - node name
         *     - topic name
         *     - topic type
         1. Need to fine the node to attach the topic to
            i. We assume the node is in the list
         2. Add Node to topic list
         MAIN: Desiging and setting up a peer to peer connection between nodes
         3. Inform all the prexisting nodes about the new port
         */ 
        
        // 1. 
        strcpy(cmp_node.name, received_message.node_name);
        // printf("Finding Node\n");
        node_ptr = linkedlist_find(master->active_node_registry, &cmp_node, master_compare_nodes);
        // printf("Found Node Node\n");
        // 2.
        // ! Need to check topic TYPE conflicts

        new_topic = (struct Topic*)calloc(sizeof(struct Topic), 1);
        strcpy(new_topic->topic_name, received_message.topic_name); 
        new_topic->message_type = received_message.topic_type;
        if (received_message.type == NEW_PUBLISHER)
            new_topic->type = PUBLISHER;
        else 
            new_topic->type = SUBSCRIBER; 
        
        if (linkedlist_find(node_ptr->topics, new_topic, master_compare_topics))
        {
            printf("Node{%s} already Established to topic{%s}", node_ptr->name, new_topic->topic_name);
            return;
        }

        linkedlist_append(&node_ptr->topics, new_topic);

        /*
            If New Subscriber:
                Inform ALL exisiting publishers about the port the new subscriber is on
            If New Publisher:
                Pass it a list of ports that subscribers are on
        */

        if (received_message.type == NEW_PUBLISHER)
        {
            
        }


        
    }
    else
        printf("This Message Type is not supported by cros YET\n");
    

}

void master_print_registry(struct Master *master)
{   
    printf("~~ Node Registry ~~\n");
    
    for ( LinkedListNode * node = master->active_node_registry; node != NULL; node = node->next )
    {
        struct Node* cros_node = (struct Node *)node->data;
        printf("Node Name : %s\n", cros_node->name);
        printf("Port: %d\n",  ntohs(cros_node->address.sin_port));
        printf("Topics:\n");
        for (LinkedListNode * topic_node = cros_node->topics; topic_node != NULL; topic_node = topic_node->next)
        {
            struct Topic* topic = (struct Topic *)topic_node->data;
            printf("\t %s\n", topic->topic_name);
        }
        printf("\n");
    }   

    // for (struct Node * node = master->registry.active_nodes; node != NULL; node = node->next)
    // {
    //     printf("Node { %s } At Port (%d):", node->name, ntohs(node->address.sin_port));

    //     for(struct Topic * topic = node->topics; topic != NULL; topic = topic->next)
    //     {
    //         printf(" %s ( %s ) | ", topic->topic_name, topic->type == SUBSCRIBER ? "SUB": "PUB");
    //     } 

    //     printf("\n");

    // }
    printf("~~ ~~ ~~ ~~ ~~ ~~ ~~");

}

int master_compare_nodes(void * node1, void * node2)
{
    struct Node * n1 = (struct Node *) node1, 
                * n2 = (struct Node *) node2;
    if ( strcmp(n1->name, n2->name) == 0 )
        return 1;
    return 0;

}

int master_compare_topics(void * topic1, void * topic2)
{
    struct Topic * t1 = (struct Topic *) topic1, 
                * t2 = (struct Topic *) topic2;
    if ( strcmp(t1->topic_name, t2->topic_name) == 0 )
        return 1;
    return 0;

}
