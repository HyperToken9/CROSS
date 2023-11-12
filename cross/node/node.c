
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
    // printf("Assigned Port Number: %d\n", ntohs(nh->reading_address.sin_port));

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


        printf("From master? : %d\n", incoming_message.from_master);
        printf("Topic Name: %s\n", incoming_message.topic_name);
        

        if (incoming_message.from_master)
        {
            printf("Node Recieved Message from master\n");
            // Master Says ... 
            // There is Node X at port P 
            // That is subscribed to topic T
            // Which you publish to

            NodePort* new_port = (NodePort*)calloc(sizeof(NodePort),1);

            // new_port->next = 0;
            new_port->address = incoming_message.address;


            // 1. Find that publication
            LinkedListNode * publication = nh->publications;

            while (strcmp(((Publication *)publication->data)->topic_name, 
                            incoming_message.topic_name) != 0)
                publication = publication->next;
            
            // printf("Length of subscibed nodes : %d\n", 
            // linkedlist_length(((Publication *)publication->data)->subscribed_nodes));

            /* Add Port to the subscribed nodes of the Publication */         
            // linkedlist_append(&((Publication *)publication->data)->subscribed_nodes, 
                                // new_port);
            
            // printf("Length of subscibed nodes : %d\n", 
            // linkedlist_length(((Publication *)publication->data)->subscribed_nodes));

        }
        else
        {
            printf("Recieved Data from subscribed topic\n");
            
            // Find Subscription
            Subscription* subscription;
            LinkedListNode* traversal_ptr;
            
            // printf("Length : %d\n", linkedlist_length(nh->subscriptions));

            // printf("Topic A : %s\n", incoming_message.topic_name);
            // printf("Topic B : %s\n", ((Subscription*)nh->subscriptions->data )->topic_name);


            for (traversal_ptr = nh->subscriptions; 
                strcmp(( (Subscription*)traversal_ptr->data )->topic_name, 
                        incoming_message.topic_name) != 0; 
                traversal_ptr = traversal_ptr->next)
                ;
                // printf("Not FOuhnd\n");
            // printf("Exiting %d\n", traversal_ptr);
            // printf("Topic B : %s\n", ((Subscription*)traversal_ptr->data )->topic_name);
        
            subscription = (Subscription*)traversal_ptr->data;
            printf("Found Subscription For Topic : %s\n", subscription->topic_name);

            // Recieve Data From Publisher
            if (subscription->message_type == CROS_MSG_TYPE_STRING)
            {
                printf("Need to Recieve String\n");

                // Read Length of string;
                unsigned int size;
                read(socket_descriptor, &size, sizeof(size));
                printf("Size of Incoming String :%d\n", size);

                char * data = (char *)calloc(size, sizeof(char));
                read(socket_descriptor, data, size);
                // printf("")
                subscription->callback_ptr(data);
                
            }
            else
                printf("Error: Unable to Transmit this data-type\n");

            // Tigger Callback

            // subscription->callback_ptr();

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
