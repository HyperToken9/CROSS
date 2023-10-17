
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "node_handle.h"
#include "../messages/master.h"

void init_node(struct NodeHandle *nh, char name[]);