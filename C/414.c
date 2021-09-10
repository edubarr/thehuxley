#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 1001

typedef struct queue
{
    int current_size;
    int head;
    int tail;
    int items[MAX_QUEUE_SIZE];
} queue;

queue *create_queue();
void enqueue(queue *queue, int item);
int compare(const void *x, const void *y);

int main()
{
    int n, m, nota, count;
    

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        queue *alunos = create_queue();
        scanf("%d", &m);
        int aux[MAX_QUEUE_SIZE - 1];
        count = 0;
        alunos->tail = MAX_QUEUE_SIZE - 1;

        for (int j = 0; j < m; j++)
        {
            scanf("%d", &nota);
            enqueue(alunos, nota);
            aux[j] = nota;
        }
        qsort(alunos->items, m, sizeof(int), compare);

        for (int k = 0; k < m; k++)
        {
            if (aux[k] == alunos->items[k])
            {
                count++;
            }
        }
        printf("%d\n", count);
    }
}

int compare(const void *x, const void *y)
{
    return *(int *)y - *(int *)x;
}

queue *create_queue()
{
    queue *new_queue = (queue *)malloc(sizeof(queue));
    new_queue->current_size = 0;
    new_queue->head = 0;
    new_queue->tail = MAX_QUEUE_SIZE - 1;

    return new_queue;
}

void enqueue(queue *queue, int item)
{
    if (queue->current_size >= MAX_QUEUE_SIZE)
    {
        printf("Queue overflow.\n");
    }
    else
    {
        queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;
        queue->items[queue->tail] = item;
        queue->current_size++;
    }
}