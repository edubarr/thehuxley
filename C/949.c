#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct data
{
    int left, right;
    struct data *next;
} data;

typedef struct tree
{
    int value[9999];
    data *branch[9999];
} tree;

typedef struct head
{
    int element;
    struct head *next;
} head;

tree *create(int size);
head *addList(head *list, int element);
void addTree(tree *root, int left, int right, int index);
void print(tree *root, head *list, int level);

int main()
{
    int size, value, left, right, first;

    scanf("%d", &size);

    tree *root = create(size);

    for (int i = 0; i < size; i++)
    {
        scanf("%d %d %d", &value, &left, &right);

        root->value[i] = value;
        addTree(root, left, right, i);

        if (i == 0)
        {
            first = value;
        }
    }

    printf("Nivel 1: Maior = %d, Menor = %d\n", first, first);

    head *list = NULL;

    list = addList(list, 0);

    print(root, list, 2);

    return 0;
}

tree *create(int size)
{
    tree *newTree = malloc(sizeof(tree));

    for (int i = 0; i < size; i++)
    {
        newTree->branch[i] = NULL;
        newTree->value[i] = -9999;
    }
    return newTree;
}

head *addList(head *list, int element)
{
    head *newHead = malloc(sizeof(head));
    newHead->element = element;
    newHead->next = list;

    return newHead;
}

void addTree(tree *root, int left, int right, int index)
{
    data *newData = malloc(sizeof(data));
    newData->left = left;
    newData->right = right;
    newData->next = NULL;

    root->branch[index] = newData;
}

void print(tree *root, head *list, int level)
{
    head *newList = NULL;

    while (list != NULL)
    {
        if (root->branch[list->element]->left != -1)
        {
            newList = addList(newList, root->branch[list->element]->left);
        }

        if (root->branch[list->element]->right != -1)
        {
            newList = addList(newList, root->branch[list->element]->right);
        }

        list = list->next;
    }
    list = newList;

    if (list == NULL)
    {
        return;
    }

    int smaller = root->value[newList->element];
    int bigger = root->value[newList->element];

    newList = newList->next;

    while (newList != NULL)
    {
        if (root->value[newList->element] > bigger)
        {
            bigger = root->value[newList->element];
        }
        if (root->value[newList->element] < smaller)
        {
            smaller = root->value[newList->element];
        }
        newList = newList->next;
    }

    free(newList);

    printf("Nivel %d: Maior = %d, Menor = %d\n", level, bigger, smaller);

    print(root, list, level + 1);
}