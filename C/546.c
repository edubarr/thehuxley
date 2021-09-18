#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

typedef struct tree
{
    int data;
    struct tree *right;
    struct tree *left;
} tree;

tree *create(int element);
tree *loadTree(char *treeString, int *index);
int check(tree *root, tree *left, tree *right, int aux);

int main()
{
    char input[99999];
    scanf("%[^\n]", input);

    getchar();

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
    tree *left = root->left;
    tree *right = root->right;

    if (check(root, left, right, 1))
    {
        printf("VERDADEIRO\n");
    }
    else
        printf("FALSO\n");
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

int check(tree *root, tree *left, tree *right, int aux)
{
    if (left != NULL)
    {
        if (left->data <= root->data)
        {
            if (aux == 1)
            {
                aux = check(left, left->left, left->right, aux);

                if (aux == 0)
                {
                    return 0;
                }
            }
            else
                return 0;
        }
        else
            return 0;
    }

    if (right != NULL)
    {
        if (right->data > root->data)
        {
            if (aux == 1)
            {
                aux = check(right, right->left, right->right, aux);

                if (aux == 0)
                {
                    return 0;
                }
            }
            else
                return 0;
        }
        else
            return 0;
    }
    return 1;
}