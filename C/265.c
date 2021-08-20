#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char caracter;
    int qtd;
    struct node *next;
} node;

node *freq(char *text);
node *addHead(node *head, char carac, int qtd2);
void print(node *head);
void unload(node *head);

int main()
{
    char text[999];

    fgets(text, 999, stdin);

    node *list = freq(text);

    print(list);

    unload(list);
}

node *freq(char *text)
{
    int size = strlen(text);
    // Cabeça da lista
    node *list = malloc(sizeof(node));
    list->next = NULL;
    list->qtd = 9999;

    // Armazena a frequencia do caracter
    int charFreq;

    // Interage pela tabela ASCII e comparada com a string
    for (int i = 32; i < 256; i++)
    {
        charFreq = 0;

        for (int j = 0; j < size; j++)
        {
            if (text[j] == i)
            {
                charFreq++;
            }
        }

        if (charFreq > 0)
        {
            if (list->qtd == 9999)
            {
                list->caracter = i;
                list->qtd = charFreq;
            }
            else
            {
                list = addHead(list, i, charFreq);
            }
        }
    }
    return (list);
}

node *addHead(node *head, char carac, int qtd2)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) // Checa se conseguiu alocar memoria
    {
        printf("Error allocating memory for new node!");
    }

    new_node->caracter = carac;
    new_node->qtd = qtd2;

    // Insere novo nó na lista
    new_node->next = head;
    head = new_node;

    return head;
}

void print(node *head)
{
    node *current_node = head;
    while (current_node != NULL)
    {
        printf("%c %d\n", current_node->caracter, current_node->qtd);

        current_node = current_node->next;
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