#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

void unload(node *head);
node *load(int size);
void compare(node *list1, int size1, node *list2, int size2);

int main()
{
    int na, nb;

    //Lê o tamanho da lista e chama a função para carrega-la
    scanf("%d", &na);
    node *list_a = load(na);

    scanf("%d", &nb);
    node *list_b = load(nb);

    compare(list_a, na, list_b, nb); //Compara a possível sublista com a lista

    //Libera a memória das listas
    unload(list_a);
    unload(list_b);

    return 0;
}

// Função para carregar a lista
node *load(int size)
{
    node *head = malloc(sizeof(node)); //Aloca a cabeça da lista

    scanf("%d", &head->number); //Carrega o primeiro valor na cabeça da lista
    head->next = NULL;

    // Lê o restante dos valores e insere no começo da lista
    for (int j = 1; j < size; j++)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) // Checa se conseguiu alocar memoria
        {
            unload(head);
            printf("Error allocating memory for new node!");
        }

        scanf("%d", &new_node->number);

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

// Função para comparar a sublista com a lista
void compare(node *list1, int size1, node *list2, int size2)
{
    int count = 0;

    node *current2 = list2;

    for (int i = 0; i < size2; i++)
    {
        node *current1 = list1;

        for (int j = 0; j < size1; j++)
        {
            if (current2->number == current1->number)
            {
                count++;
                break;
            }
            current1 = current1->next;
        }
        current2 = current2->next;
    }

    if (count == size2)
    {
        printf("1");
    }
    else
    {
        printf("0");
    }
}