#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack stack;

//Armazena o conteudo do no e um ponteiro para o proximo no da pilha
typedef struct _node node;

struct _stack
{
    node *top;
};
struct _node
{
    int element;
    node *next;
};

//Cria uma stack com o a head NULL
stack *create_stack()
{
    stack *new_stack = (stack *)malloc(sizeof(stack));
    new_stack->top = NULL;
    return new_stack;
}

//Verifica se a pilha esta vazia
int is_empty(stack *stack)
{
    if (stack->top == NULL)
        return 1;
    else
        return 0;
}

//Recebe uma pilha e Retorna o elemento que esta no topo da fila
int pop(stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack Underflow\n");
        return -1;
    }
    else
    {
        int num = stack->top->element;
        node *tmpP = stack->top;
        stack->top = stack->top->next;

        free(tmpP);
        return num;
    }
}

//Recebe uma pilha e um inteiro e retorna a nova pilha
//Adiciona um novo node no topo da pilha
void push(stack *stack, int element)
{
    node *new_top = malloc(sizeof(node));
    new_top->element = element;
    new_top->next = stack->top;
    stack->top = new_top;
    //printf("Push of %d complete\n", stack->top->element);
}

//Recebe a pilha e a operacao a ser feita
//faz a operacao da calculadora
void result(stack *stack, char operation)
{
    int termo1 = pop(stack);
    int termo2 = pop(stack);

    int resultado;

    switch (operation)
    {
    case '+':
        resultado = termo2 + termo1;
        break;

    case '-':
        resultado = termo2 - termo1;
        break;

    case '*':
        resultado = termo2 * termo1;
        break;

    case '/':
        resultado = termo2 / termo1;
        break;
    }

    push(stack, resultado);
}

//Recebe uma pilha vazia e quantas strings serao lidas
//Le as n strings que vao seguir e resolve as expressoes
void calculadora(stack *calculadora, int size)
{
    char buffer[9999];
    for (int i = 0; i < size; i++)
    {
        getchar();
        scanf("%s", buffer);

        if (!strcmp(buffer, "+"))
        {
            result(calculadora, '+');
        }
        else if (!strcmp(buffer, "-"))
        {
            result(calculadora, '-');
        }
        else if (!strcmp(buffer, "*"))
        {
            result(calculadora, '*');
        }
        else if (!strcmp(buffer, "/"))
        {
            result(calculadora, '/');
        }
        else
        {
            push(calculadora, atoi(buffer));
        }
    }
}

int main()
{
    stack *equacao = create_stack();
    int k;
    scanf("%d", &k);
    calculadora(equacao, k);
    printf("Coordenada 1: %d\n", pop(equacao));
    scanf("%d", &k);
    calculadora(equacao, k);
    printf("Coordenada 2: %d\n", pop(equacao));
}
//Insira o código aqui