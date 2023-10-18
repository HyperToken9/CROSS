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
        
        printf("Thread Created  ");
        sleep(2);
        
        // if (fork() == 0)
        // {
        //     // Child Process
        //     master_process_incoming_connection(&master);

        //     // TODO: Currently the fork terminates here
        //     // TODO: Need to merge data coming from initialized nodes
        // }
        // else
        // {
        //     // Parent Process 
            // master_close_connection(&master);
        // }

    }

    master_close(&master); 

    return 0;
}

/* 
    Future TODO:
        Adding Time to message
*/
