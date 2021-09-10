#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int item;
    struct node *next;
} node;

typedef struct stack
{
    node *top;
} stack;

stack *create_stack();
void push(stack *stack);
int pop(stack *stack);
int is_empty(stack *stack);

int main()
{
    char action[7];

    int count = 0;

    stack *back = create_stack();
    stack *forward = create_stack();

    while (scanf("%s", action) != EOF)
    {
        if (!strcmp(action, "ENTER"))
        {
            if (count != 0)
            {
                push(back);
                pop(forward);
            }
            count++;
        }
        else if (!strcmp(action, "BACK"))
        {
            push(forward);
            pop(back);
        }
        else if (!strcmp(action, "FORWARD"))
        {
            pop(forward);
            push(back);
        }
    }
    
    printf("BACK: %d\n", pop(back));
    printf("FORWARD: %d\n", pop(forward));

    return 0;
}

stack *create_stack()
{
    stack *new_stack = malloc(sizeof(stack));
    node *new_top = malloc(sizeof(node));

    new_top->item = 0;
    new_top->next = NULL;

    new_stack->top = new_top;
    return new_stack;
}

void push(stack *stack)
{
    node *new_top = malloc(sizeof(node));
    if (stack->top == NULL)
    {
        new_top->item = 1;
    }
    else
    {
        new_top->item = stack->top->item + 1;
    }
    new_top->next = stack->top;
    stack->top = new_top;
}

int pop(stack *head)
{
    if (head->top == NULL)
    {
        return 0;
    }
    else
    {
        int tmp = head->top->item;
        node *tmpP = head->top;
        head->top = head->top->next;

        free(tmpP);
        return tmp;
    }
}

int is_empty(stack *stack)
{
    if (stack->top->item == 0)
        return 1;
    else
        return 0;
}