#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct access
{
    node *head;
    int list_size;
} access;

typedef struct hash
{
    int size;
    int elements_number;
    access *positions;
} hash;

struct hash *create(int size);

void add(hash *hashTable, int element, int operation);
void del(hash *hashTable, int element, int operation);
void has(hash *hashTable, int element, int operation);
void prt(hash *hashTable, int operation);

int high_factor(hash *hashTable);
hash *rehash(hash *hashTable);
void copy(hash *hashTable, hash *new);
void add_n(hash *hashTable, int element);

int main()
{
    hash *hashTable = create(7);

    char command[3];
    int element, operation = 0;

    while (scanf("%s", command) != EOF)
    {
        if (!strcmp(command, "ADD"))
        {
            scanf("%d", &element);

            add(hashTable, element, operation);

            if (high_factor(hashTable))
            {
                hashTable = rehash(hashTable);
            }
        }
        if (!strcmp(command, "DEL"))
        {
            scanf("%d", &element);
            del(hashTable, element, operation);
        }
        if (!strcmp(command, "HAS"))
        {
            scanf("%d", &element);
            has(hashTable, element, operation);
        }
        if (!strcmp(command, "PRT"))
        {
            scanf("%d", &element);
            prt(hashTable, operation);
        }
        operation++;
    }

    return 0;
}

hash *create(int size)
{
    hash *newHashTable = malloc(sizeof(hash));
    newHashTable->size = size;
    newHashTable->elements_number = 0;

    newHashTable->positions = malloc(size * sizeof(hash));

    for (int i = 0; i < size; i++)
    {
        newHashTable->positions[i].head = NULL;
        newHashTable->positions[i].list_size = 0;
    }

    return newHashTable;
}

void add(hash *hashTable, int element, int operation)
{
    int k = element % hashTable->size;

    node *newHashTable = malloc(sizeof(node));
    newHashTable->data = element;

    if (hashTable->positions[k].head == NULL)
    {
        newHashTable->next = NULL;

        hashTable->positions[k].head = newHashTable;
        hashTable->positions[k].list_size = 1;

        printf("%d %d %d\n", operation, 1, 0);

        hashTable->elements_number++;
    }
    else
    {
        int comp = 0, flag = 0, added = 0;

        node *aux = hashTable->positions[k].head;

        while (aux != NULL)
        {
            comp++;

            if (aux->data == element)
            {
                flag = 1;
                break;
            }
            aux = aux->next;
        }

        if (flag == 0)
        {
            newHashTable->next = hashTable->positions[k].head;

            hashTable->positions[k].head = newHashTable;
            hashTable->positions[k].list_size++;

            added = 1;

            hashTable->elements_number++;
        }
        printf("%d %d %d\n", operation, added, comp);
    }
}

void del(hash *hashTable, int element, int operation)
{
    int k = element % hashTable->size;

    struct node *aux = hashTable->positions[k].head;

    if (aux == NULL)
    {
        printf("%d %d %d\n", operation, 0, 0);
    }
    else if (aux->next == NULL && aux->data != element)
    {
        printf("%d %d %d\n", operation, 0, 1);
    }
    else
    {
        node *rmv;

        if (aux->data == element)
        {
            rmv = aux;
            hashTable->positions[k].head = aux->next;

            printf("%d %d %d\n", operation, 1, 1);

            hashTable->positions[k].list_size--;
            hashTable->elements_number--;

            free(rmv);

            return;
        }

        int found = 0, comp = 1;

        while (aux->next != NULL)
        {
            comp++;
            if (aux->next->data == element)
            {
                found = 1;
                break;
            }
            aux = aux->next;
        }
        if (found == 1)
        {
            rmv = aux->next;

            aux->next = aux->next->next;

            hashTable->positions[k].list_size--;
            hashTable->elements_number--;

            printf("%d %d %d\n", operation, 1, comp);

            free(rmv);

            return;
        }
        else
        {
            printf("%d %d %d\n", operation, 0, comp);
        }
    }
}

void has(hash *hashTable, int element, int operation)
{
    int k = element % hashTable->size;

    node *aux = hashTable->positions[k].head;

    int found = 0, comp = 0;

    while (aux != NULL)
    {
        comp++;
        if (aux->data == element)
        {
            found = 1;
            break;
        }
        aux = aux->next;
    }

    printf("%d %d %d\n", operation, found, comp);
}

void prt(hash *hashTable, int operation)
{
    int bigger = -1;

    for (int i = 0; i < hashTable->size; i++)
    {
        if (hashTable->positions[i].list_size > bigger)
        {
            bigger = hashTable->positions[i].list_size;
        }
    }

    printf("%d %d %d %d\n", operation, hashTable->size, hashTable->elements_number, bigger);
}

int high_factor(hash *hashTable)
{
    double elements = hashTable->elements_number;
    double size = hashTable->size;

    double fc = elements / size;

    if (fc < 0.75)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

hash *rehash(hash *hashTable)
{
    hash *newHashTable = create((hashTable->size * 2) - 1);

    copy(hashTable, newHashTable);

    return newHashTable;
}

void copy(hash *hashTable, hash *new)
{
    node *aux;

    new->elements_number = hashTable->elements_number;

    for (int i = 0; i < hashTable->size; i++)
    {
        aux = hashTable->positions[i].head;

        while (aux != NULL)
        {
            add_n(new, aux->data);

            aux = aux->next;
        }
    }
}

void add_n(hash *hashTable, int element)
{
    int k = element % hashTable->size;

    node *newHashTable = malloc(sizeof(node));

    newHashTable->data = element;

    if (hashTable->positions[k].head == NULL)
    {
        newHashTable->next = NULL;

        hashTable->positions[k].head = newHashTable;
        hashTable->positions[k].list_size = 1;

        return;
    }
    else
    {
        newHashTable->next = hashTable->positions[k].head;

        hashTable->positions[k].head = newHashTable;
        hashTable->positions[k].list_size++;
    }
}