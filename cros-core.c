#include "cross/master/master.h"

/*
    To Build:
        make
    To Execute:
        ./cros-core.o
*/

int main()
{   
    pthread_t connect_thread;

    struct Master master;

    master_init(&master);    

    while(1)
    {
        // printf("Setting Listening");
        master_listen(&master);
        
        // printf("Recievend Conenctions\n");

        pthread_create(&connect_thread, NULL, 
                       &master_process_incoming_connection,
                       (void *) & master);
        
        // master_process_incoming_connection(&master);


        master_wait_thread_initialization(&master);
        
    }

    // master_close(&master); 

    return 0;
}

/* 
    Future TODO:
        Adding Time to message
*/
