#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000

typedef struct node
{
    int numbers[N];
    struct node *next;
} node;

node *push(node *stack);
node *pop(node *stack);

int main()
{

    node *stack = NULL;

    char control[4];

    while (scanf("%s", control) != EOF)
    {
        if (strcmp(control, "PUSH") == 0)
        {
            stack = push(stack);
        }
        else
        {
            stack = pop(stack);
        }
    }

    return 0;
}

node *push(node *stack)
{
    node *newNode = malloc(sizeof(node));
    int n, i = 0;

    while (scanf("%d", &n))
    {
        newNode->numbers[i] = n;

        i++;
    }
    newNode->numbers[i] = -1;

    newNode->next = stack;
    stack = newNode;

    return stack;
}

node *pop(node *stack)
{
    if (stack == NULL)
    {
        printf("EMPTY STACK\n");
        return NULL;
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
    return stack;
}