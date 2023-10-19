
#pragma once

#include "../messages/types.h"

struct Subscriber{
    char topic_name[50];
    enum CROS_MessageTypes message_type;
};

typedef struct Subscriber Subscriber;