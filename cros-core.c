#include "cross/master/master.h"

int main()
{
    struct Master master;

    master_init(&master, 80800);        

    return 0;
}