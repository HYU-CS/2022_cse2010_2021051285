#include <stdio.h>
#include <stdlib.h>

int list[7] = {38, 27, 43, 3, 9, 82, 10};

typedef int DataType;

void swap(DataType *lhs, DataType *rhs)
{
    DataType temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

int partition(DataType *src, int left, int right)
{
    int pivot = src[(left + right) / 2];
    swap(src + left, src + (left + right) / 2);

    int lCursor = left + 1;
    int rCursor = right;

    while(lCursor <= rCursor)
    {
        if(src[lCursor] > pivot && src[rCursor] < pivot)
        {
            swap(src + lCursor, src + rCursor);
        }

        if(src[lCursor] <= pivot && lCursor <= right)
        {
            lCursor += 1;
        }

        if(src[rCursor] >= pivot && rCursor >= left)
        {
            rCursor -= 1;
        }
    }

    swap(src + left, src + rCursor);

    return rCursor;
}

void quickSort(DataType *src, int left, int right)
{
    if(left >= right)
    {
        return;
    }

    int mid = partition(src, left, right);
    quickSort(src, left, mid - 1);
    quickSort(src, mid + 1, right);
}


int main(void)
{
    quickSort(list, 0, 6);

    for(int i = 0; i < 7; i++)
    {
        printf("%d\t", list[i]);
    }

    printf("\n");

    return 0;
}