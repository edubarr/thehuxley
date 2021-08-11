#include <stdio.h>
#include <stdlib.h>

#define N 20

typedef struct node
{
    int number;
    struct node *next;
} node;

node *load(int size);
void unload(node *head);
void compare(node *list1, node *list2);
void bubbleSort(node *head);

void print(node *head);

int main()
{
    // Chama função para carregar as listas
    node *array_1 = load(N);
    node *array_2 = load(N);

    bubbleSort(array_1);
    bubbleSort(array_2);

    //    print(array_1);
    //    print(array_2);

    // Chama função para comparar a interseção das listas
    compare(array_1, array_2);

    // Libera a memória
    unload(array_1);
    unload(array_2);

    return 0;
}

// Função para carregar a lista
node *load(int size)
{
    node *head = malloc(sizeof(node)); // Aloca a cabeça da lista

    // Carrega o primeiro valor na cabeça da lista
    scanf("%d", &head->number);
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
        scanf("%d", &new_node->number);
        new_node->next = NULL;

        // Faz a inserção do novo nó como último e atualiza o ponteiro para o último nó
        last->next = new_node;
        last = new_node;
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

// Função para comparar as listas e printar a interseção
void compare(node *list1, node *list2)
{
    int count = 0;
    int prev = 999999999;

    node *current2 = list2; // Cria um ponteiro que será o nó atual no loop

    // Percorre as listas e compara
    while (current2 != NULL)
    {
        node *current1 = list1; // Cria um ponteiro que será o nó atual no loop

        while (current1 != NULL)
        {
            if (current2->number == current1->number)
            {
                if (current1->number != prev) // Checa se já foi printado o mesmo numero
                {
                    printf("%d\n", current1->number);
                }

                prev = current1->number;

                count++;
            }
            current1 = current1->next;
        }
        current2 = current2->next;
    }
    if (count == 0)
    {
        printf("VAZIO");
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