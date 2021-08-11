#include <stdio.h>
#include <stdlib.h>

#define N 9

typedef struct node
{
    int number;
    struct node *next;
} node;

void unload(node *head);
node *load();
node *invert(node *head);
void print(node *head);

int main()
{
    node *list = load();
    if (list == NULL)
    {
        unload(list);
        return 1;
    }

    node *invertedList = invert(list);
    if (invertedList == NULL)
    {
        unload(list);
        unload(invertedList);
        return 1;
    }

    print(invertedList);

    unload(list);
    unload(invertedList);
}

// Função para carregar a lista
node *load()
{
    node *head = malloc(sizeof(node)); //Aloca a cabeça da lista
    if (head == NULL)                  // Checa se conseguiu alocar memoria
    {
        unload(head);
        printf("Error allocating memory for new node!");
        return NULL;
    }

    scanf("%d", &head->number); //Carrega o primeiro valor na cabeça da lista
    head->next = NULL;

    node *last = head; // Cria um ponteiro que será sempre o último nó da lista
    if (last == NULL)  // Checa se conseguiu alocar memoria
    {
        unload(last);
        printf("Error allocating memory for new node!");
        return NULL;
    }

    int buffer;

    // Lê o restante dos valores e insere no final da lista
    while (scanf("%d", &buffer) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) // Checa se conseguiu alocar memoria
        {
            unload(new_node);
            unload(head);
            printf("Error allocating memory for new node!");
            return NULL;
        }

        new_node->number = buffer;
        new_node->next = NULL;

        // Insere novo nó na lista
        last->next = new_node;
        last = new_node;
    }

    return head;
}

node *invert(node *head)
{
    // Cria uma cópia do ponteiro da lista original e um para a lista invertida
    node *head1 = head;
    node *headInverted = malloc(sizeof(node));
    if (headInverted == NULL) // Checa se conseguiu alocar memoria
    {
        unload(headInverted);
        printf("Error allocating memory for new head!");
        return NULL;
    }

    // Insere o valor na cabeça da lista
    headInverted->number = head1->number;
    headInverted->next = NULL;

    // Avança o ponteiro para o próximo nó
    head1 = head1->next;

    // Loop para alimentar a lista invvertida
    while (head1 != NULL)
    {
        // Aloca memória para novo nó e checa se foi alocado corretamente.
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload(head1);
            unload(headInverted);
            printf("Error allocating memory for new node");

            return NULL;
        }

        // Alimenta o novo nó e insere na nova lista.
        new_node->number = head1->number;

        head1 = head1->next;

        new_node->next = headInverted;
        headInverted = new_node;
    }

    return headInverted;
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