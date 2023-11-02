
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "node_handle.h"

#include "../messages/node_to_master.h"
#include "../messages/node_to_node.h"

#include "../networking/networking.h"

void node_init(NodeHandle *nh, char name[]);

void* node_initialize_reading_thread(void * arguments);

void node_connect_to_master(NodeHandle *nh);

void node_message_master(NodeHandle *nh, NodeToMasterMessage message);

void node_disconnect_from_master(NodeHandle *nh);
