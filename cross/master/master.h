#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>


#include "master_struct.h"
#include "../messages/master.h"
#include "../messages/print.h"


void master_init(struct Master *master);

void master_listen(struct Master *master);

void* master_process_incoming_connection(void* arg); //(struct Master *master);

void master_close_connection(struct Master *master);

void master_close(struct Master *master);
