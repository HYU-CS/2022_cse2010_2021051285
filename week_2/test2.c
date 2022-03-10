#include <stdio.h>
#define SIZE 10

int list[SIZE] = {38, 27, 1, 43, 3, 9, 82, 10, 16, 60};

void selectionSort(int list[], int n)
{	
    for(int i = 0; i < n - 1; i++)
    {
        int tmp;
        int least = i;

        for(int j = i + 1; j < n; j++)
        {
            if(list[j] < list[least])
            {
                least = j;
            }
        }

        tmp = list[i];
        list[i] = list[least];
        list[least] = tmp;
    }
}

int main(void)
{
    puts("Before Sorting");
    for(int i = 0; i < SIZE; i++)
    {
        printf("%d ", list[i]);
    }
    puts("");

    selectionSort(list, SIZE);

    puts("After Sorting");
    for(int i = 0; i < SIZE; i++)
    {
        printf("%d ", list[i]);
    }
    puts("");

    return 0;
}
