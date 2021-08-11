#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

node *load();
void unload(node *head);
void bubbleSort(node *head);
void print(node *head);

int main()
{
    node *list = load();

    bubbleSort(list);

    print(list);
}

node *load()
{
    node *head = malloc(sizeof(node)); //Aloca a cabeça da lista

    scanf("%d", &head->number); //Carrega o primeiro valor na cabeça da lista
    head->next = NULL;

    int buffer;

    // Lê o restante dos valores e insere no começo da lista
    while (scanf("%d", &buffer) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) // Checa se conseguiu alocar memoria
        {
            unload(head);
            printf("Error allocating memory for new node!");
        }

        new_node->number = buffer;

        // Insere novo nó na lista
        new_node->next = head;
        head = new_node;
    }

    return head;
}

// Função para liberar a memória
void unload(node *head)
{
    // Ponteiro temporário para armazenar o ponteiro do nó a ser liberado
    node *tmp;

    // Loop que libera a memória
    while (head != NULL)
    {
        tmp = head->next;

        free(head);

        head = tmp;
    }
}

void swap(node *a, node *b)
{
    int temp = a->number;
    a->number = b->number;
    b->number = temp;
}

// Função para ordenar as listas
void bubbleSort(node *head)
{
    int swapped;
    node *headcopy;
    node *buffer = NULL;

    // Verificando se a lista não está vazia.
    if (head == NULL)
        return;

    // Usando BubbleSort para ordenar.
    do
    {
        swapped = 0;
        headcopy = head;

        while (headcopy->next != buffer)
        {
            if (headcopy->number > headcopy->next->number)
            {
                swap(headcopy, headcopy->next);
                swapped = 1;
            }
            headcopy = headcopy->next;
        }
        buffer = headcopy;
    } while (swapped);
}

void print(node *head)
{
    node *current_node = head;
    while (current_node != NULL)
    {
        printf("%d ", current_node->number);

        current_node = current_node->next;
    }
    printf("\n");
}