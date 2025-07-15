#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "main.h"

int main()
{
    int a = 0;
    int b = 0;
    int res = 0;
    int isWork = 1;
    int sel = 0;
    while (isWork)
    {
        printMenu();
        scanf("%d",&sel);
        switch (sel)
        {
        case 1:
            getTwoNumber(&a, &b);
            res = add(a, b);
            printf("Результат: %d \n",res);
            break;
        case 2:
            getTwoNumber(&a, &b);
            res = sub(a, b);
            printf("Результат: %d \n",res);
            break;
        case 3:
            getTwoNumber(&a, &b);
            res = mult(a, b);
            printf("Результат: %d \n",res);
            break;
        case 4:
            getTwoNumber(&a, &b);
            res = divi(a, b);
            printf("Результат: %d \n",res);
            break;
        case 5:
            isWork = 0;
            break;
        default:
            printf("Нет такого пункта\n");
            break;
        }
    }
    exit(EXIT_SUCCESS);
}
