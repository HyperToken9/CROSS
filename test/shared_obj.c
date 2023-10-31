#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include<unistd.h>


struct Share{
    int a;
};

void set(struct Share *s, int a)
{
    s->a = a;
    printf("S->A == %d\n", a);

}

void* func(void* arg)
{
    // pthread_detach(pthread_self());
    printf("In thread\n");
    struct Share * share = (struct Share *)arg;

    printf("Share a : %d\n", share->a);
    
    
    // sleep(5);
    share->a = 7;
    // printf("Done Sleeping\n");
    // pthread_exit(NULL);
    pthread_detach(pthread_self());
    sleep(5);
    printf("Done Done\n");
    while(1){}
}

int main()
{
    pthread_t ptid;

    struct Share share;

    set(&share, 5);

    pthread_create(&ptid, NULL, &func, (void *)&share);
    
    printf("Waiting\n");
    sleep(2);
    pthread_join(ptid, NULL);
    printf("Joined\n");
    sleep(10);
    // sleep(1);
    // share.a = 9;
    // pthread_create(&ptid, NULL, &func, (void *)&share);
    // sleep(10);
    // printf("New Share A : %d\n", share.a);
    printf("Exiting\n");
    return 0;
}