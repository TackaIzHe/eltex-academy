#include <stdio.h>

int task2()
{
    int number = 0;
    int buf = 0;
    printf("Задание №2 \n");
    printf("Введите число от 1 до 99: ");
    scanf("%2d", &number);
    int n[number];

    for (int i = 0; i < number; i++)
    {
        n[i] = i + 1;
    }

    for (int i = 0; i < number/2; i++)
    {
        buf = n[i];
        n[i] = n[number-i -1];
        n[number -i -1] = buf;
    }

    for (int i = 0; i<number; i++)
    {
        printf("%d ",n[i]);
    }
    printf("\n");
    return 0;
}