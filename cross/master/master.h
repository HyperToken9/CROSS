#pragma once
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>


#include "struct.h"


void master_init(struct Master *master, int port_no);
