#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "subscriber_handle.h"

#include "../node/node_handle.h"
#include "../node/node.h" // Get Rid of this -- Add dependencies to Networking

#include "../messages/node_to_master.h"
#include "../messages/types.h"

// void subscriber_init(Subscriber* string_publisher, NodeHandle* nh, char topic_name[], enum CROS_MessageTypes type);
void subscriber_init(Subscriber* subscriber, NodeHandle* nh, char topic_name[], void (*callback_ptr)(void *, unsigned int));
