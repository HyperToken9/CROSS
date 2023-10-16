
#include "master.h"

void master_init(struct Master *master, int port_no)
{

    master->listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    master->address.sin_family = AF_INET;
    master->address.sin_addr.s_addr = inet_addr("127.0.0.1");
    master->address.sin_port = htons(port_no);
    
    bind(master->listen_sd, (struct sockaddr*)&master->address, sizeof(master->address));

    listen(master->listen_sd, 5);

    // master_address.sin_family = AF_INET;
    // master_address.

    printf("Master Listening At Port %d\n", port_no);
}



 