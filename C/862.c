#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int index;
    int digit;
    struct node *next;
} node;

node *load(char *sequence, int size);
void unload(node *head);
void seq(node *head);

int main()
{
    node *list;
    char sequence[99];

    scanf("%s", sequence);
    int size = strlen(sequence);

    while (size != 1)
    {
        list = load(sequence, size);

        seq(list);

        unload(list);

        scanf("%s", sequence);
        size = strlen(sequence);
    }
}

// Função para carregar a lista inserindo no final
node *load(char *sequence, int size)
{
    node *head = malloc(sizeof(node)); // Aloca a cabeça da lista

    // Carrega o primeiro valor na cabeça da lista
    head->digit = (int)sequence[0] - '0';
    head->index = 0;
    head->next = NULL;

    node *last = head; // Cria um ponteiro que será sempre o último nó da lista

    // Lê o restante dos valores e insere no final da lista
    for (int i = 1; i < size; i++)
    {
        // Aloca a memória e checa se foi alocada corretamente
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload(head);
            printf("Error allocating memory for new node");
        }

        // Lê o próximo valor, insere no novo nó e define o próximo ponteiro como NULL
        new_node->digit = (int)sequence[i] - '0';
        new_node->index = i;
        new_node->next = NULL;

        // Faz a inserção do novo nó como último e atualiza o ponteiro para o último nó
        last->next = new_node;
        last = new_node;
    }
    return head;
}

// Função para liberar memória
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

// Função pra calcular a maior sequencia
void seq(node *head)
{
    node *currentNode = head;

    int start = 0, end = 0, bigSeq = 0, tmpSeq = 0, bigStart = 0, bigEnd = 0;

    while (currentNode != NULL)
    {
        if (currentNode->digit == 0)
        {
            start = currentNode->index;
            end = currentNode->index;
            tmpSeq = 0;
            while (currentNode != NULL && currentNode->digit == 0)
            {
                currentNode = currentNode->next;
                if (currentNode != NULL && currentNode->digit == 0)
                {
                    end = currentNode->index;
                    tmpSeq++;
                }
            }
        }
        if (tmpSeq > bigSeq)
        {
            bigStart = start;
            bigEnd = end;
            bigSeq = tmpSeq;
        }
        if (currentNode != NULL)
            currentNode = currentNode->next;
    }
    printf("%d %d\n", bigStart, bigEnd);
}