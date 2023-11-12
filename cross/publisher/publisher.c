

#include "publisher.h"


void publisher_init(Publisher* publisher, NodeHandle* nh, char topic_name[], enum CROS_MessageTypes type)
{
    // printf("PUBLIHER INIT: Sends A NODE INIT TYPE MESSage\n");
    // printf("PUBLISHER Needs to be initialized after the node ")
    // ! Pulisher Needs to be initialized after the Node: 

    if (nh->is_registered == 0)
    {
        printf("Initilized the Node before declaring Publishers\n");
        exit(0);
    }

    strcpy(publisher->topic_name, topic_name);
    publisher->message_type = type;


    Publication * new_publication = (Publication *)calloc(sizeof(Publication), 1);
    strcpy(new_publication->topic_name, topic_name);

    node_connect_to_master(nh);

    NodeToMasterMessage message;
    message.type = NEW_PUBLISHER;
    message.topic_type = type;
    strcpy(message.topic_name, topic_name);
    strcpy(message.node_name, nh->node_name);
    
    node_message_master(nh, message);

    NodeToNodeMessage incomming_message;
    int flag;
    NodePort * nodeport_ptr;

    while(1)
    {
        flag = read(nh->writing_socket_descriptor, 
                    &incomming_message, sizeof(NodeToNodeMessage));

        if (flag < 0)
            perror("Master Error receiving data");
        if (incomming_message.address.sin_port == 0)
            break;

        nodeport_ptr = (NodePort*)calloc(sizeof(NodePort), 1);
        nodeport_ptr->address = incomming_message.address;
        
        linkedlist_append(&new_publication->subscribed_nodes, nodeport_ptr);

        printf("Recieved %s at Port Back %d\n", incomming_message.topic_name, ntohs(incomming_message.address.sin_port));
        
    }

    linkedlist_append(&nh->publications, new_publication);

    printf("No of Publications : %d\n", linkedlist_length(nh->publications));
    // linkedlist_print(nh->publications, publisher_print_publications);

    node_disconnect_from_master(nh);

}


void publisher_publish(Publisher* publisher, NodeHandle* nh, void * data, unsigned int data_size)
{
    // 1. Create Message
    // 2. For each subscriber in subscription in list
    //       i. Connect 
    //      ii. Send Message

    NodeToNodeMessage message;

    Publication* publication;
    NodePort* node_port;
    int socket_descriptor;

    LinkedListNode* travesal_ptr;

    message.from_master = 0;
    strcpy(message.topic_name, publisher->topic_name);

    travesal_ptr = nh->publications;

    while( strcmp(((Publication *)travesal_ptr->data)->topic_name, 
                    publisher->topic_name) != 0 )
        travesal_ptr = travesal_ptr->next;
    
    publication = (Publication *) travesal_ptr->data;
    printf("Found Publication\n");


    travesal_ptr = publication->subscribed_nodes;

    while (travesal_ptr != NULL)
    {
        node_port = (NodePort *) travesal_ptr->data;

        socket_descriptor = networking_socket_init(node_port->address);

        write(socket_descriptor, &message, sizeof(message));

        if (publication->message_type == CROS_MSG_TYPE_STRING)
        {
            printf("Need To Send String\n");
            // Send Data Size

            write(socket_descriptor, &data_size, sizeof(data_size));
            write(socket_descriptor, data, data_size);
            printf("Sent Messages\n");
        }
        else
            printf("Error: Unable to Transmit this data-type\n");


        close(socket_descriptor);
        travesal_ptr = travesal_ptr->next;
    }

    


}

// void publisher_print_publications(void * data)
// {
//     Publication * publication = (Publication *) data;
// }