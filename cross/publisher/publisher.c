

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

// void publisher_print_publications(void * data)
// {
//     Publication * publication = (Publication *) data;
// }