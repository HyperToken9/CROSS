
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "node_handle.h"
#include "../messages/node_to_master.h"

void node_init(struct NodeHandle *nh, char name[]);