

#include "subscriber.h"


void subscriber_init(Subscriber* subscriber, NodeHandle* nh, char topic_name[], enum CROS_MessageTypes type)
{
    
    if (nh->is_registered == 0)
    {
        printf("Initilized the Node before declaring Subscribers\n");
        exit(0);
    }

    node_connect_to_master(nh);

    NodeToMasterMessage message;
    message.type = NEW_SUBSCRIBER;
    message.topic_type = type;
    strcpy(message.topic_name, topic_name);
    strcpy(message.node_name, nh->node_name);
    
    node_message_master(nh, message);

    node_disconnect_from_master(nh);

}