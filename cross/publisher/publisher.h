#pragma once

#include <stdio.h>
#include <string.h>

#include "publisher_handle.h"

#include "../node/node_handle.h"
#include "../node/node.h"

#include "../messages/node_to_master.h"
#include "../messages/types.h"

void publisher_init(Publisher* string_publisher, NodeHandle* nh, char topic_name[]);

void publisher_publish(Publisher* publisher, NodeHandle* nh, void * data, unsigned int data_size);

