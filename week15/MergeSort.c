#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef int DataType;

DataType list[7] = {38, 27, 43, 3, 9, 82, 10};

void merge(DataType *src, DataType *dest, int left, int mid, int right)
{
    int index = left;
    int i = left;
    int j = mid + 1;

    while(i <= mid && j <= right)
    {
        if(src[i] < src[j])
        {
            dest[index] = src[i];
            index++;
            i++;
        }
        else
        {
            dest[index] = src[j];
            index++;
            j++;
        }
    }

    while(i <= mid)
    {
        dest[index] = src[i];
        index++;
        i++;
    }

    while(j <= right)
    {
        dest[index] = src[j];
        index++;
        j++;
    }
}

void mergeSortRecursive(DataType *src, DataType *temp, int left, int right)
{
    if(left >= right)
    {
        return;
    }

    int mid = (left + right) / 2;
    
    mergeSortRecursive(temp, src, left, mid);
    mergeSortRecursive(temp, src, mid + 1, right);

    merge(temp, src, left, mid, right);
}

void mergeSort(DataType *src, int left, int right)
{
    DataType *temp = (DataType *)malloc(sizeof(DataType) * (right - left + 1));
    memcpy(temp, src, sizeof(DataType) * (right - left + 1));
    mergeSortRecursive(src, temp, left, right);
}

int main(void)
{
    mergeSort(list, 0, 6);

    for(int i = 0; i < 7; i++)
    {
        printf("%d\t", list[i]);
    }

    printf("\n");

    return 0;
}