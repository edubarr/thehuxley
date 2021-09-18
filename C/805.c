#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

typedef struct data
{
    int element;
    struct data *next;
} data;

typedef struct graph_t
{
    data *table[9999];
    int visited[9999];
    int prev[9999];
} graph_t;

typedef struct queue_t
{
    data *head;
} queue_t;

void sort(data *head);
queue_t *createQueue();
void enqueue(queue_t *queue, int element);
int dequeue(queue_t *queue);
int is_empty(queue_t *queue);
int count(graph_t *graph, int start, int end);
void width_travel(graph_t *graph, int start, int end);
node *addNode(node *head, int element);
void printTable(graph_t *graph, int start, int end, int size, int qnt);
graph_t *createGraph(int size);
data *createData(int element);
void add_conection(graph_t *graph, int x, int y);

int main()
{
    int size, connections, cases;

    scanf("%d %d %d\n", &size, &connections, &cases);

    graph_t *graph = createGraph(size);

    int x, y;

    for (int i = 0; i < connections; i++)
    {
        scanf("%d %d", &x, &y);
        add_conection(graph, x, y);
    }

    for (int i = 0; i < size; i++)
    {
        sort(graph->table[i]);
    }

    int start, end;

    for (int i = 0; i < cases; i++)
    {
        printf("--------\n\n");

        int qnt = 0;

        scanf("%d %d", &start, &end);

        data *aux = graph->table[start];

        while (graph->table[start] != NULL)
        {
            graph->table[start] = graph->table[start]->next;

            qnt++;
        }
        graph->table[start] = aux;

        printf("Caso de Teste #%d - BFS(%d)\n\n", i + 1, start);

        width_travel(graph, start, end);
        printTable(graph, start, end, size, qnt);

        for (int j = 0; j < size; j++)
        {
            graph->visited[j] = 0;
            graph->prev[j] = -1;
        }
    }

    free(graph);

    printf("--------\n");

    return 0;
}

void sort(data *head)
{
    if (head == NULL)
    {
        return;
    }

    int aux;
    data *height_i;
    data *height_j;
    data *height_end = NULL;

    for (height_i = head; height_i->next != NULL; height_i = height_i->next)
    {
        for (height_j = head; height_j->next != height_end; height_j = height_j->next)
        {
            if (height_j->element > height_j->next->element)
            {
                aux = height_j->element;
                height_j->element = height_j->next->element;
                height_j->next->element = aux;
            }
        }
        height_end = height_j;
    }
}

queue_t *createQueue()
{
    queue_t *newQueue = malloc(sizeof(queue_t));
    newQueue->head = NULL;

    return newQueue;
}

void enqueue(queue_t *queue, int element)
{
    data *newData = malloc(sizeof(data));
    newData->element = element;

    if (queue->head == NULL)
    {
        newData->next = queue->head;
        queue->head = newData;
    }
    else
    {
        data *aux = queue->head;

        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = newData;
        newData->next = NULL;
    }
}

int dequeue(queue_t *queue)
{
    int element = queue->head->element;
    queue->head = queue->head->next;

    return element;
}

int is_empty(queue_t *queue)
{
    if (queue->head == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int count(graph_t *graph, int start, int end)
{
    int count = 0;

    if (start == end)
    {
        return 0;
    }

    if (graph->prev[end] == -1)
    {
        return -999;
    }

    while (graph->prev[end] != start)
    {
        if (graph->prev[end] == -1)
        {
            return -999;
        }
        count++;
        end = graph->prev[end];
    }
    count++;
    return count;
}

void width_travel(graph_t *graph, int start, int end)
{
    printf("Iniciando busca em largura a partir de %d\n", start);

    queue_t *queue = createQueue();
    int dequeued;
    data *adjacent = graph->table[start];
    graph->visited[start] = 1;

    enqueue(queue, start);

    while (!is_empty(queue))
    {
        dequeued = dequeue(queue);
        adjacent = graph->table[dequeued];

        while (adjacent != NULL)
        {
            if (graph->visited[adjacent->element] == 0)
            {
                printf("Iniciando busca em largura a partir de %d\n", adjacent->element);
                graph->visited[adjacent->element] = 1;
                enqueue(queue, adjacent->element);
                graph->prev[adjacent->element] = dequeued;
            }
            adjacent = adjacent->next;
        }
    }

    printf("\n");

    free(queue);
}

node *addNode(node *head, int element)
{
    node *newNode = malloc(sizeof(node));
    newNode->value = element;
    newNode->next = head;
    return newNode;
}

void printTable(graph_t *graph, int start, int end, int size, int qnt)
{
    int aux;

    for (int i = 0; i < size; i++)
    {
        graph->visited[i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        aux = count(graph, start, i);

        if (aux == -999)
        {
            printf("%d | - | -\n", i);
        }
        else
        {
            printf("%d | %d | ", i, aux);

            if (graph->prev[i] == -1)
            {
                printf("-\n");
            }
            else
            {
                printf("%d\n", graph->prev[i]);
            }
        }
        for (int j = 0; j < size; j++)
        {
            graph->visited[j] = 0;
        }
    }

    printf("\n");

    node *head = NULL;

    if (start == end)
    {
        printf("Caminho entre %d e %d: %d\n\n", start, end, start);
        return;
    }

    if (graph->prev[end] == -1)
    {
        printf("Sem caminho entre %d e %d\n\n", start, end);
        return;
    }

    head = addNode(head, end);
    int aux_end = end;

    while (graph->prev[end] != start)
    {
        if (graph->prev[end] == -1)
        {
            printf("Sem caminho entre %d e %d\n\n", start, end);
            return;
        }

        head = addNode(head, graph->prev[end]);
        end = graph->prev[end];
    }

    head = addNode(head, graph->prev[end]);

    end = aux_end;

    printf("Caminho entre %d e %d: %d", start, end, start);

    head = head->next;

    while (head != NULL)
    {
        printf(" => %d", head->value);
        head = head->next;
    }
    printf("\n\n");
}

graph_t *createGraph(int size)
{
    graph_t *newGraph = malloc(sizeof(graph_t));

    for (int i = 0; i < size; i++)
    {
        newGraph->table[i] = NULL;
        newGraph->visited[i] = 0;
        newGraph->prev[i] = -1;
    }
    return newGraph;
}

data *createData(int element)
{
    data *newData = malloc(sizeof(data));
    newData->element = element;
    newData->next = NULL;

    return newData;
}

void add_conection(graph_t *graph, int x, int y)
{
    data *newNode = createData(y);
    newNode->next = graph->table[x];
    graph->table[x] = newNode;
}