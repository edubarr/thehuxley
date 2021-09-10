#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

typedef struct node
{
    char par;
    struct node *next;
} node;

node *push(node *stack, char carac);
node *pop(node *stack);
void unload(node *head);

int main()
{
    int n;

    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        node *stack = NULL;
        char buffer[1000];
        char car;
        int no = 0;

        fgets(buffer, 1000, stdin);

        int size = strlen(buffer);

        for (int j = 0; j < size; j++)
        {
            car = buffer[j];

            if (car == '(' || car == '[')
            {
                stack = push(stack, car);
            }

            if (car == ')' || car == ']')
            {
                if (stack == NULL)
                {
                    printf("No\n");
                    no++;
                }
                else if (stack->par == '(' && car == ')')
                {
                    stack = pop(stack);
                }
                else if (stack->par == '[' && car == ']')
                {
                    stack = pop(stack);
                }
            }
        }

        if (!no)
        {
            if (stack == NULL)
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
                unload(stack);
            }
        }
    }
}

node *push(node *stack, char carac)
{
    node *newNode = malloc(sizeof(node));

    newNode->par = carac;

    newNode->next = stack;
    stack = newNode;

    return stack;
}

node *pop(node *stack)
{
    if (stack == NULL)
    {
        return stack;
    }
    else
    {
        node *temp = stack;
        stack = stack->next;

        free(temp);

        return stack;
    }
}

void unload(node *head)
{
    node *tmp;
    while (head != NULL)
    {
        tmp = head->next;

        free(head);

        head = tmp;
    }
}