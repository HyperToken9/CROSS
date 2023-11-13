
#include <stdio.h>

#include "cross/node/node.h"
#include "cross/publisher/publisher.h"

#include "matrix.h"

int main(int argc, char* argv[])
{

    NodeHandle nh;
    Publisher matrix_publisher;
    Matrix matrix;

    node_init(&nh, "matrix_publisher");

    publisher_init(&matrix_publisher, &nh, "matrix");


    while(1)
    {   
        printf("Enter Matrix: ");
        
        read_matrix(&matrix);

        publisher_publish(&matrix_publisher, &nh, matrix, sizeof(matrix));
    }
     
    return 0;
}
