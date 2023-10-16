#pragma once

struct Master{
    
    int listen_sd, connect_sd;
    
    struct sockaddr_in address;

};

