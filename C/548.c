#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef struct node
{
    int numbers[N];
    struct node *next;
} node;

void push(node *stack, int *array);
void pop(node *stack);

int main()
{

    node *stack = NULL;

    char control[4];

    while (scanf("%s", control) != EOF)
    {
        if (strcmp(control, "PUSH") == 0)
        {
            int array[N], i = 0, n;

            while (scanf("%d", n))
            {
                array[i] = n;

                i++;
            }
            push(stack, array);
        }
        else
        {
            pop(stack);
        }
        
    }

    return 0;
}

void push(node *stack, int *array)
{
    node *newNode = malloc(sizeof(node));

    memcpy(newNode->numbers, array, N * sizeof(int));

    newNode->next = stack;
    stack = newNode;
}

void pop(node *stack)
{
    if (stack == NULL)
    {
        printf("EMPTY STACK");
        return;
    }
    else
    {
        for (int i = 0; stack->numbers[i] != -1; i++)
        {
            printf("%d", stack->numbers[i]);

            if (stack->numbers[i + 1] != -1)
            {
                printf(" ");
            }
        }
        printf("\n");

        node *temp = stack;
        stack = stack->next;

        free(temp);
    }
}