#include "../../messages/types.h"

struct TopicList
{   
    char topic_name[50];
    enum CROS_MessageTypes message_type;

    enum NodeTopicRelation type;
    
    struct TopicList *next;
    
};

