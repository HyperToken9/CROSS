
struct Matrix
{
    int size;
    int array[100][100];
};

typedef struct Matrix Matrix;


void read_matrix(Matrix * matrix)
{
    printf("Enter Dimensions of Matrix: ");
    scanf("%d", &matrix->size);
    
    for (int i = 0; i < matrix->size; i++)
    {
        printf("Enter Row %d: ", i);
        for (int j = 0; j < matrix->size; j++)
            scanf("%d", &(matrix->array[i][j]));

    }

}

void print_matrix(Matrix matrix)
{
    for (int i = 0; i < matrix.size; i++)
    {
        for (int j = 0; j < matrix.size; j++)
            printf("%d  ", matrix.array[i][j]);

        printf("\n");
        
    }
}

void multiply_matrix(Matrix * matrix, int factor)
{
    for (int i = 0; i < matrix->size; i++)
    {
        for (int j = 0; j < matrix->size; j++)
            matrix->array[i][j] *= factor;

        printf("\n");
        
    }
}

void invert_matrix(Matrix * matrix)
{
    int temp;
    for (int i = 0; i < matrix->size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            temp = matrix->array[i][j];
            matrix->array[i][j] = matrix->array[j][i];
            matrix->array[j][i] = temp;
        }
    }
}
