#include <stdio.h>
#include <math.h>

int main()
{
    int level, potencia;

    scanf("%d", &level);

    if (level >= 1 && level <= 20)
    {
        potencia = 20 + pow(level, 3);
    }
    else if (level > 20 && level <= 40)
    {
        potencia = 8000 + pow(level - 10, 2);
    }
    else if (level > 40 && level <= 60)
    {
        potencia = 9000 + (5 * level);
    }
    else if (level > 60 && level <= 80)
    {
        potencia = 9300 + (2 * level);
    }
    else if (level > 80 && level <= 100)
    {
        potencia = 9500 + level;
    }

    printf("Potencia de : %d W", potencia);

    return 0;
}