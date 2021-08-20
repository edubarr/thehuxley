#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int digit;
    struct node *next;
} node;

node *load();
void unload(node *head);
node *listSum(node *number1, node *number2);
node *trimLeft(node *number);
void print(node *head);

int main()
{
    node *number1 = load();
    node *number2 = load();
    if (number1 == NULL && number2 == NULL)
    {
        printf("Lista vazia!\n");
        return 0;
    }

    node *sum = listSum(number1, number2);
    sum = trimLeft(sum);

    print(sum);

    unload(number1);
    unload(number2);
    unload(sum);
}

node *load() // Carrega a lista inserindo nó no começo
{
    node *head = malloc(sizeof(node)); //Aloca a cabeça da lista
    char bufferc;
    int buffer;

    scanf("%c", &bufferc);            //Carrega o primeiro valor na cabeça da lista e verifica se o digito é um numero
    if (bufferc < 48 || bufferc > 57) //Verifica se o primeiro valor lido não é um simbolo
    {
        return NULL;
    }
    head->digit = (int)bufferc - '0';
    head->next = NULL;

    // Lê o restante dos valores e insere no começo da lista

    while (scanf("%d", &buffer))
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) // Checa se conseguiu alocar memoria
        {
            unload(head);
            printf("Error allocating memory for new node!");
        }

        new_node->digit = buffer;

        // Insere novo nó na lista
        new_node->next = head;
        head = new_node;
    }
    getchar();
    return head;
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

node *listSum(node *number1, node *number2)
{
    int tmpSum, tmpD = 0;
    node *sum = malloc(sizeof(node));
    if (sum == NULL) // Checa se conseguiu alocar memoria
    {
        printf("Error allocating memory for new node!");
    }
    sum->next = NULL;

    if (number1 == NULL && number2 != NULL)
    {
        tmpSum = number2->digit;
    }
    else if (number2 == NULL && number1 != NULL)
    {
        tmpSum = number1->digit;
    }
    else
    {
        tmpSum = number1->digit + number2->digit;
    }

    if (tmpSum >= 10)
    {
        tmpD = tmpSum / 10;
        tmpSum = tmpSum % 10;
    }

    sum->digit = tmpSum;
    if (number1 != NULL)
    {
        number1 = number1->next;
    }
    if (number2 != NULL)
    {
        number2 = number2->next;
    }

    while (number1 != NULL || number2 != NULL || tmpD > 0)
    {

        if (number1 == NULL && number2 == NULL)
        {
            tmpSum = tmpD;
        }
        else if (number1 == NULL && number2 != NULL)
        {
            tmpSum = number2->digit + tmpD;
        }
        else if (number2 == NULL && number1 != NULL)
        {
            tmpSum = number1->digit + tmpD;
        }
        else
        {
            tmpSum = number1->digit + number2->digit + tmpD;
        }

        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) // Checa se conseguiu alocar memoria
        {
            printf("Error allocating memory for new node!");
        }
        if (tmpSum >= 10)
        {
            tmpD = tmpSum / 10;
            tmpSum = tmpSum % 10;
        }
        else
        {
            tmpD = 0;
        }

        new_node->digit = tmpSum;
        // Insere novo nó na lista
        new_node->next = sum;
        sum = new_node;

        if (number1 != NULL)
        {
            number1 = number1->next;
        }
        if (number2 != NULL)
        {
            number2 = number2->next;
        }
    }

    return sum;
}

node *trimLeft(node *number)
{
    node *tmp;
    while (number->digit == 0)
    {
        tmp = number->next;

        free(number);

        number = tmp;
    }
    return number;
}

void print(node *head)
{
    node *current_node = head;
    while (current_node != NULL)
    {
        printf("%d ", current_node->digit);

        current_node = current_node->next;
    }
    printf("\n");
}