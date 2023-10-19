#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>


#include "structs/master_struct.h"
#include "structs/node_list.h"

#include "../messages/node_to_master.h"
#include "../messages/print.h"


void master_init(struct Master *master);

void master_print_registry(struct Master *master);

void master_listen(struct Master *master);

void master_wait_thread_initialization(struct Master *master);

void* master_process_incoming_connection(void* arg); //(struct Master *master);

void master_process_message(struct Master *master, NodeToMasterMessage message);

// void master_close_connection(struct Master *master);
// void master_close(struct Master *master);
