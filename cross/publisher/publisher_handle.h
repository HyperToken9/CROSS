
#pragma once

#include "../messages/types.h"

struct Publisher{
    char topic_name[50];
    // enum CROS_MessageTypes message_type;
};

typedef struct Publisher Publisher;