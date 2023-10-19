#pragma once

enum NodeToMasterMessageType{
    NODE_INIT,
    NEW_SUBSCRIBER,
    NEW_PUBLISHER
};

enum NodeTopicRelation{
    SUBSCRIBER,
    PUBLISHER,
    SERVER,
    CLIENT
};

enum CROS_MessageTypes{
    CROS_MSG_TYPE_STRING,
    CROS_MSG_TYPE_INT,

};