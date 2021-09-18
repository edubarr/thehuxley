#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *next;
} node;

int hashKey(int item, int m);
node **loadHashTable(node **hashtable, int m, int c);
node *insertList(node *head, int key);
void printHash(node **hashTable, int m);

int main()
{
    int n, m, c;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &m, &c);

        node *hashtmp[m];

        node **hashTable;

        hashTable = loadHashTable(hashtmp, m, c);

        printHash(hashTable, m);

        if (i < (n - 1))
        {
            printf("\n");
        }
    }
}

int hashKey(int item, int m)
{
    return item % m;
}

node **loadHashTable(node *hashTable[], int m, int c)
{
    int keyBuffer;
    for (int i = 0; i < m; i++)
    {
        hashTable[i] = NULL;
    }

    for (int i = 0; i < c; i++)
    {
        scanf("%d", &keyBuffer);

        hashTable[hashKey(keyBuffer, m)] = insertList(hashTable[hashKey(keyBuffer, m)], keyBuffer);
    }

    return hashTable;
}

node *insertList(node *head, int key)
{
    node *newNode = malloc(sizeof(node));
    node *last = head;

    newNode->key = key;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;

        return head;
    }
    else
    {
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = newNode;

        return head;
    }
}

void printHash(node **hashTable, int m)
{
    node *tmp;
    for (int i = 0; i < m; i++)
    {
        printf("%d -> ", i);

        tmp = hashTable[i];

        while (tmp != NULL)
        {
            printf("%d -> ", tmp->key);

            tmp = tmp->next;
        }
        printf("\\\n");
    }
}