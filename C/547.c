#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tree
{
    int data;
    struct tree *right;
    struct tree *left;
} tree;

tree *create(int element);
tree *loadTree(char *treeString, int *index);
int check(tree *root, int aux, int element, int level);

int main()
{
    char input[99999];
    int element;
    scanf("%[^\n]", input);
    getchar();
    scanf("%d", &element);

    int index = 0, size = strlen(input);
    char treeString[size];

    for (int i = 0, j = 0; i < size; i++)
    {
        if (!isspace(input[i]))
        {
            treeString[j] = input[i];
            j++;
        }
    }

    tree *root = loadTree(treeString, &index);

    int aux = check(root, -1, element, 0);

    if (aux == -1)
    {
        printf("NAO ESTA NA ARVORE\n-1\n");
    }
    else
        printf("ESTA NA ARVORE\n%d\n", aux);

    return 0;
}

tree *create(int element)
{
    tree *newTree = malloc(sizeof(tree));

    newTree->data = element;
    newTree->right = NULL;
    newTree->left = NULL;

    return newTree;
}

tree *loadTree(char *treeString, int *index)
{
    tree *newTree = NULL;

    if (treeString[*index] == '(')
    {
        *index += 1;
        if (treeString[*index] == ')')
        {
            *index += 1;
            return NULL;
        }

        char number[100];
        int j = 0, intNumber;

        while (treeString[*index] != '(')
        {
            number[j] = treeString[*index];
            j++;
            *index += 1;
        }

        number[j] = '\0';

        intNumber = atoi(number);

        newTree = create(intNumber);
        newTree->left = loadTree(treeString, index);
        newTree->right = loadTree(treeString, index);
    }
    *index += 1;
    return newTree;
}

int check(tree *root, int aux, int element, int level)
{
    int empty = 0;

    if (root->data == element)
    {
        return level;
    }

    if (root->left != NULL)
    {
        level += 1;
        empty = 1;

        aux = check(root->left, aux, element, level);

        if (aux != -1)
        {
            return aux;
        }
    }

    if (root->right != NULL)
    {
        if (empty == 0)
        {
            level += 1;
        }

        aux = check(root->right, aux, element, level);

        if (aux != -1)
        {
            return aux;
        }
    }

    if (aux == -1)
    {
        level -= 1;
        return -1;
    }
    else
        return level;
}