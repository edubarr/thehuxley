#include <stdio.h>
#include <string.h>

int posi(char letra);

int main()
{
    int n, l, size;
    char string[50];

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int hash = 0;
        scanf("%d", &l);

        for (int j = 0; j < l; j++)
        {
            scanf("%s", string);

            size = strlen(string);

            for (int k = 0; k < size; k++)
            {
                hash += posi(string[k]) + j + k;
            }
        }
        printf("%d\n", hash);
    }
}

int posi(char letra)
{
    return letra - 65;
}