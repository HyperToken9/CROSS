#pragma once

enum NodeToMasterMessageType{
    INIT_NODE,
    NEW_SUBSCRIBER,
    NEW_PUBLISHER
};

enum NodeTopicRelation{
    SUBSCRIBER,
    PUBLISHER,
    SERVER,
    CLIENT
};
