#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "cross/node/node.h"
#include "cross/subscriber/subscriber.h"


void callback1(void * data, unsigned int data_size)
{   
    char * string = (char *)data; 
    
    printf("Recicieved String : %s\n", string);

    /* Toggle Case */
    for (int i = 0; i < strlen(string); i++)
    {
        if (isalpha(string[i] ))
            string[i] ^= ' ';
    }
       
    

    printf("Processed String: %s\n", string);

}

void callback2(void * data, unsigned int data_size)
{   
    char * string = (char *)data; 
    char temp;
    printf("Recicieved String : %s\n", string);

    /* Reverse String */
    for (int i = 0; i < strlen(string)/2; i++)
    {
        temp = string[i];
        string[i] = string[strlen(string) - i - 1];
        string[strlen(string) - i - 1] = temp;
    }

    printf("Processed String: %s\n", string);

}

int main(int argc, char* argv[])
{

    NodeHandle nh;
    Subscriber matrix_subscriber;

    node_init(&nh, "string_processor");

    subscriber_init(&matrix_subscriber, &nh, "string_toggle", callback1);
    subscriber_init(&matrix_subscriber, &nh, "string_reverse", callback2);

    // Dont Quit
    while(1);

    return 0;
}