#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _deque deque_t;
typedef struct _node node_t;

//Guarda um ponteiro pro node anterior, para o proximo node e o valor guardado
struct _node
{
    node_t *prev;
    node_t *next;
    int value;
};

//Guarda um ponteiro para o primeiro node, um ponteiro para o ultimo node, e o tamanho do deque
struct _deque
{
    node_t *front;
    node_t *rear;
    int size;
};

//Cria um node que guarda os valores que são enfileirados no deque
node_t *node_new(int value);

//Cria um deque dinamicamente e retorna seu endereço de memoria
deque_t *construct();
//Libera a memória do conteúdo e do próprio deque
void destruct(deque_t *deque);

//Retorna o tamanho do deque
int size(deque_t *deque);
//Retorna verdadeiro se o deque esta vazio, caso contrário, retorna falso
bool empty(deque_t *deque);

//Retorna o valor da frente da lista, retorna int_min quando a lista estiver vazia
int front(deque_t *deque);
//Retorna o valor do fim da lista, retorna int_min quando a lista estiver vazia
int rear(deque_t *deque);

//Cria um nó que guarda um valor e o adiciona ao fim do deque
void enqueue_rear(deque_t *deque, int value);
//Cria um nó que guarda um valor e o adiciona ao inicio do deque
void enqueue_front(deque_t *deque, int value);
//Retira o valor do final caso não esteja vazia
void dequeue_rear(deque_t *deque);
//Retira o valor da frente caso não esteja vazia
void dequeue_front(deque_t *deque);
//Limpa o conteudo do deque(deixa ele vazio)
void erase(deque_t *deque);

//Imprime o deque em uma unica linha, com os elementos separados por um espaço,
//terminando com um \n, lembrando de respeitar os conceitos de fila.
void print(deque_t *deque);

int main()
{
    int i, num;
    scanf("%d", &num);

    deque_t *deque = construct();

    int vector[num];
    for (i = 0; i < num; ++i)
        scanf("%d", &vector[i]);
    for (i = 0; i < num; ++i)
        enqueue_rear(deque, vector[i]);

    
    printf("%d\n", front(deque));
    printf("%d\n", rear(deque));
    
    if (!empty(deque))
        printf("The size of the deque %d\n", size(deque));
    else
        printf("The deque is empty\n");

    scanf("%d", &num);
    for (i = 0; i < num; ++i)
        enqueue_front(deque, i);
    print(deque);
    dequeue_front(deque);
    print(deque);
    dequeue_rear(deque);
    print(deque);

    erase(deque);
    for (i = 0; i < 3; ++i)
        enqueue_rear(deque, i);

    print(deque);
    destruct(deque);

    return 0;
}

//Insira o código aqui
//Cria um node que guarda os valores que são enfileirados no deque
node_t *node_new(int value)
{
    node_t *novo_node = (node_t *)malloc(sizeof(node_t));
    novo_node->value = value;
    novo_node->next = NULL;
    novo_node->prev = NULL;

    return novo_node;
}

//Cria um deque dinamicamente e retorna seu endereço de memoria
deque_t *construct()
{
    deque_t *novo_deque = (deque_t *)malloc(sizeof(deque_t));
    novo_deque->front = NULL;
    novo_deque->rear = NULL;
    novo_deque->size = 0;

    return novo_deque;
}
//Libera a memória do conteúdo e do próprio deque
void destruct(deque_t *deque)
{
    node_t *front_node = deque->front;

    node_t *nodetmp = NULL;

    for (int i = 0; i < deque->size; i++)
    {
        nodetmp = front_node->next;

        free(front_node);

        front_node = nodetmp;
    }
    free(deque);
}

//Retorna o tamanho do deque
int size(deque_t *deque)
{
    return deque->size;
}
//Retorna verdadeiro se o deque esta vazio, caso contrário, retorna falso
bool empty(deque_t *deque)
{
    if (deque->size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Retorna o valor da frente da lista, retorna int_min quando a lista estiver vazia
int front(deque_t *deque)
{
    if (empty(deque))
    {
        return INT_MIN;
    }
    else
    {
        return deque->front->value;
    }
}
//Retorna o valor do fim da lista, retorna int_min quando a lista estiver vazia
int rear(deque_t *deque)
{
    if (empty(deque))
    {
        return INT_MIN;
    }
    else
    {
        return deque->rear->value;
    }
}

//Cria um nó que guarda um valor e o adiciona ao fim do deque
void enqueue_rear(deque_t *deque, int value)
{
    node_t *novo_node;
    novo_node = deque->rear;

    deque->rear = node_new(value);
    deque->rear->prev = novo_node;
    deque->rear->next = NULL;

    if (novo_node != NULL)
    {
        novo_node->next = deque->rear;
    }

    if (deque->front == NULL)
    {
        deque->front = deque->rear;
    }
    deque->size++;
}
//Cria um nó que guarda um valor e o adiciona ao inicio do deque
void enqueue_front(deque_t *deque, int value)
{
    node_t *novo_node;
    novo_node = deque->front;

    deque->front = node_new(value);
    deque->front->next = novo_node;
    deque->front->prev = NULL;

    if (novo_node != NULL)
    {
        novo_node->prev = deque->front;
    }

    if (deque->rear == NULL)
    {
        deque->rear = deque->front;
    }
    deque->size++;
}
//Retira o valor do final caso não esteja vazia
void dequeue_rear(deque_t *deque)
{
    if (deque == NULL)
    {
        return;
    }
    node_t *tmp = deque->rear;

    deque->rear = deque->rear->prev;
    deque->rear->next = NULL;
    deque->size--;

    free(tmp);
}
//Retira o valor da frente caso não esteja vazia
void dequeue_front(deque_t *deque)
{
    if (deque == NULL)
    {
        return;
    }
    node_t *tmp = deque->front;

    deque->front = deque->front->next;
    deque->front->prev = NULL;
    deque->size--;

    free(tmp);
}
//Limpa o conteudo do deque(deixa ele vazio)
void erase(deque_t *deque)
{
    node_t *tmp;
    while (deque->front != NULL)
    {
        tmp = deque->front->next;
        free(deque->front);

        deque->front = tmp;
    }

    deque->rear = NULL;
    deque->size = 0;
}

//Imprime o deque em uma unica linha, com os elementos separados por um espaço,
//terminando com um \n, lembrando de respeitar os conceitos de fila.
void print(deque_t *deque)
{
    if (deque == NULL)
        return;
    node_t *tmp = deque->front;
    while (tmp != NULL)
    {
        printf("%d", tmp->value);
        tmp = tmp->next;
        if (tmp != NULL)
        {
            printf(" ");
        }
    }
    printf("\n");
}