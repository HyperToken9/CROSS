#include<stdio.h>

#include "cross/node/node.h"
#include "cross/subscriber/subscriber.h"

#include "matrix.h"

void callback(void * data, unsigned int data_size)
{   
    Matrix * matrix = (Matrix *)data; 
    
    matrix_multiply(&matrix, 2);

    print_matrix(matrix);

}

int main(int argc, char* argv[])
{

    NodeHandle nh;
    Subscriber matrix_subscriber;

    node_init(&nh, "matrix_doubler");

    subscriber_init(&matrix_subscriber, &nh, "matrix", callback);

    // Dont Quit
    while(1);

    return 0;
}