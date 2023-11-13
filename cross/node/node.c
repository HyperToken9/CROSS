
#include "node.h"


void node_init(NodeHandle *nh, char name[])
{
    /* Catch Errors */
    // if (nh->is_registered) 
    // {
    //     printf("Node Can Only Be Initialized Once\n");
    //     exit(0);
    // }

    if ( strcmp(name, "") == 0 ) 
    {
        printf("Node Needs A Valid Name\n");
        exit(0);
    }

    /* Initialize Node Handle */
    strcpy(nh->node_name, name);
    nh->publications = NULL;
    nh->subscriptions = NULL;

    // Set Up a socket where Other Nodes Message the Node
    /* Initialize Reading Socket */
    nh->reading_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    nh->reading_address.sin_family = AF_INET;
    nh->reading_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    nh->reading_address.sin_port = 0; // Random Assignment

    if (bind(nh->reading_socket_descriptor, 
            (struct sockaddr *)& nh->reading_address,
            sizeof(nh->reading_address))< 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    listen(nh->reading_socket_descriptor, 10);

    /* Use getsockname to retrieve the actual port number */ 
    socklen_t addr_len = sizeof(nh->reading_address);
    getsockname(nh->reading_socket_descriptor, (struct sockaddr *)&nh->reading_address, &addr_len);

    // Display the assigned port number

    /* Initialize Registry Mutex*/ 
    if (pthread_mutex_init(&nh->registry_lock, NULL) != 0) { 
        printf("\n Registry Lock Failed\n"); 
        exit(EXIT_FAILURE);
    } 

    /* Create Node Reading Thread */
    pthread_create(&nh->reading_thread, NULL, 
                   &node_initialize_reading_thread,
                   (void *) nh);
    

    /* Get Registered with Master */

    /* Conenct with master */
    node_connect_to_master(nh);

    /* Create Message */
    NodeToMasterMessage message;
    message.type = INIT_NODE;
    strcpy(message.node_name, name);
    message.node_address = nh->reading_address;

    node_message_master(nh, message);

    node_disconnect_from_master(nh);

    nh->is_registered = 1;
    
}

void* node_initialize_reading_thread(void * arguments)
{
    NodeHandle* nh = (NodeHandle*) arguments;
    int socket_descriptor, flag;
    
    socklen_t length;
    // printf("Node %s has initialized reading thread\n", nh->node_name);
    while(1) // TODO : Use a variable in arguments instead
    {
        length = sizeof(struct sockaddr_in);
        socket_descriptor = accept(nh->reading_socket_descriptor, 
                                   (struct sockaddr*)&nh->reading_address,
                                   &length);

        if (socket_descriptor < 0)
        {
            printf("Accept Failed\n");
            printf("Error Code: %d\n", socket_descriptor);
        }  


        /* Reading Incoming Messages */
        /*
            Where can the messages come from 
                - Master Node
                - Other Nodes

            What type of messages can we expect
            from master
                - Ports of new nodes publishing to a topic
            other nodes
                - Publications
        */
        NodeToNodeMessage incoming_message;
        flag = read(socket_descriptor, &incoming_message, sizeof(incoming_message)); 

        if (flag < 0)
            perror("Master Error receiving data");


        if (incoming_message.from_master)
        {
            // Master Says ... 
            // There is Node X at port P 
            // That is subscribed to topic T
            // Which you publish to

            NodePort* new_port = (NodePort*)calloc(sizeof(NodePort),1);

            // new_port->next = 0;
            new_port->address = incoming_message.address;


            // 1. Find that publication
            LinkedListNode * traversal_ptr = nh->publications;
            Publication * publication;

            while (strcmp(((Publication *)traversal_ptr->data)->topic_name, 
                            incoming_message.topic_name) != 0)
                traversal_ptr = traversal_ptr->next;
            // printf("Need to add new port\n");
            publication = traversal_ptr->data;
            linkedlist_append(&publication->subscribed_nodes, new_port);

        }
        else
        {
            
            unsigned int size;
            void * data;

            // Find Subscription
            Subscription* subscription;
            LinkedListNode* traversal_ptr;
            

            for (traversal_ptr = nh->subscriptions; 
                strcmp(( (Subscription*)traversal_ptr->data )->topic_name, 
                        incoming_message.topic_name) != 0; 
                traversal_ptr = traversal_ptr->next)
                ;

            subscription = (Subscription*)traversal_ptr->data;
            // printf("Found Subscription For Topic : %s\n", subscription->topic_name);


            /* Recieve Size of Data */
            read(socket_descriptor, &size, sizeof(size));
            // printf("Size of Incoming String :%d\n", size);

            /* Allocate Memory */
            data = calloc(size, 1);

            /* Recieve Data */
            read(socket_descriptor, data, size);

            /* Trigger Call Back */
            subscription->callback_ptr(data, size);

            /* Deallocate Memory */
            free(data);

        }

        close(socket_descriptor);

    }
}

void node_connect_to_master(NodeHandle *nh)
{

    nh->writing_address = networking_address_init("127.0.0.1", 8080);

    nh->writing_socket_descriptor = networking_socket_init(nh->writing_address);

}

void node_message_master(NodeHandle *nh, NodeToMasterMessage message)
{
    int result = write(nh->writing_socket_descriptor,
                   &message, sizeof(NodeToMasterMessage));

    if (result < 0) 
    {
        perror("Error Writing NodeToMasterMessage\n");
        exit(EXIT_FAILURE);
    }
    

}

void node_disconnect_from_master(NodeHandle *nh)
{
    close(nh->writing_socket_descriptor);
}
