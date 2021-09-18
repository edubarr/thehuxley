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
void add(tree *root, tree *travel, int element);
tree *add_branch(tree *root, int element);
void print(tree *root);

int main()
{
    tree *root = NULL;

    int element;

    while (scanf("%d", &element) != EOF)
    {
        root = add_branch(root, element);

        printf("----\n");
        printf("Adicionando %d\n  ", element);
        print(root);
        printf("\n");
    }
    printf("----\n");

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

void add(tree *root, tree *travel, int element)
{
    if (element >= travel->data)
    {
        if (travel->right == NULL)
        {
            tree *newTree = create(element);

            travel->right = newTree;
            return;
        }
        else
            add(root, travel->right, element);
    }
    else
    {
        if (travel->left == NULL)
        {
            tree *newTree = create(element);

            travel->left = newTree;
            return;
        }
        else
            add(root, travel->left, element);
    }
}

tree *add_branch(tree *root, int element)
{
    if (root == NULL)
    {
        tree *newTree = create(element);

        return newTree;
    }

    tree *travel = root;

    add(root, travel, element);

    return root;
}

void print(tree *root)
{
    printf(" (");
    if (root == NULL)
    {
        printf(") ");
        return;
    }
    else
    {
        printf(" %d ", root->data);
    }
    print(root->left);
    print(root->right);
    printf(") ");
}