

#include "publisher.h"


void publisher_init(Publisher* string_publisher, NodeHandle* nh, char topic_name[], enum CROS_MessageTypes type)
{
    // printf("PUBLIHER INIT: Sends A NODE INIT TYPE MESSage\n");
    // printf("PUBLISHER Needs to be initialized after the node ")
    // ! Pulisher Needs to be initialized after the Node: 

    if (nh->is_registered == 0)
    {
        printf("Initilized the Node before declaring Publishers\n");
        exit(0);
    }

    node_connect_to_master(nh);

    NodeToMasterMessage message;
    strcpy(message.topic_name, topic_name);
    strcpy(message.node_name, nh->node_name);

    message.type = NEW_PUBLISHER;

    node_message_master(nh, message);

    node_disconnect_from_master(nh);

}