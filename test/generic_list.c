#include<stdio.h>
#include<stdlib.h>

struct Node1{
    int data;
    struct Node1* next;
};

struct Node2{
    float data;
    struct Node2* next;
};

typedef struct Node1 Node1;
typedef struct Node2 Node2;


void print_node1(Node1 node)
{
    printf("%d", node.data);
}
void print_node2(Node2 node)
{
    printf("%f", node.data);
}

Node1* init_node1(int data)
{
    Node1* new_node = (Node1*)calloc(sizeof(Node1),1);

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}
Node2* init_node2(float data)
{
    Node2* new_node = (Node2*)calloc(sizeof(Node2),1);

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}


void append(void** head, void* new_node)
{
    void* temp;

    if (*head == NULL)
        (*head) = new_node;
    else
    {
        temp = (*head);

        while(temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
    
}

void print_list1(Node1* node)
{
    Node1* temp = node;

    while(temp)
    {
        printf("%d  ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void print_list(void * node, void (*print_function_ptr)(void *))
{
    void * temp = node; 

    while(temp)
    {
        (*print_function_ptr)(temp);
        printf("  ");
        temp = temp->next;
    }

    printf("\n");

}

int main()
{
    Node1* list1 = NULL;
    Node2* list2 = NULL;

    print_list1(list1);
    list1 = init_node1(1);
    list2 = init_node2(3.6);

    print_list1(list1);


    return 0;

}

