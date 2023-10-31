#include "../cross/linkedlist/linkedlist.h"

struct Data1{
    int a;
};

typedef struct Data1 Data1;

struct Data2{
    float a;
};
typedef struct Data2 Data2;

Data1* init_data1(int a)
{
    Data1 * data = malloc(sizeof(Data1));
    data->a = a;
    return data;
}

Data2* init_data2(float a)
{
    Data2 * data = malloc(sizeof(Data2));
    data->a = a;
    return data;
}

void print_data1(Data1 * data)
{
    printf("%d ", data->a);
}

void print_data2(Data2 * data)
{
    printf("%f ", data->a);
}

int main()
{
    LinkedListNode * l1 = NULL;
    LinkedListNode * l2 = NULL;

    linkedlist_append(&l1, init_data1(1));
    linkedlist_append(&l1, init_data1(2));
    linkedlist_append(&l1, init_data1(3));

    linkedlist_append(&l2, init_data2(1.1));
    linkedlist_append(&l2, init_data2(2.2));
    linkedlist_append(&l2, init_data2(3.3));

    linkedlist_print(l1, (void (*)(void *)) print_data1);
    linkedlist_print(l2, (void (*)(void *)) print_data2);   

}
