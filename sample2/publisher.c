#include <stdio.h>

#include "cross/node/node.h"
#include "cross/publisher/publisher.h"


int main(int argc, char* argv[])
{

    NodeHandle nh;
    Publisher string_publisher1;
    Publisher string_publisher2;

    char string[50];
    int option;
    

    node_init(&nh, "string_publisher");

    publisher_init(&string_publisher1, &nh, "string_toggle");
    // printf("1: %s\n", string_publisher1.topic_name);

    publisher_init(&string_publisher2, &nh, "string_reverse");
    // printf("2: %s\n", string_publisher2.topic_name);



    while(1)
    {   
        printf("Enter A String: ");
        // fgets(string, sizeof(string), stdin);
        scanf("%s", string);

        printf("1. To Reverse A String\n");
        printf("2. To Toggle Case of String\n");
        printf("Select Option: ");

        scanf(" %d", &option);
        printf("Option Selected: %d\n", option);

        
        if (option == 1)
        {
            printf("Reversing String\n");
            publisher_publish(&string_publisher2, &nh, string, sizeof(string));
        }
        else if (option == 2)
        {
            printf("Toggling String Case\n");
            publisher_publish(&string_publisher1, &nh, string, sizeof(string));
        }  
        else
            printf("Enter A Vaild option\n");
        
    
        fflush(stdin); 
        // scanf("%s", string);
    }

    return 0;
}
