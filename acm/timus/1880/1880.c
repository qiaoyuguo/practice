/*
 * =====================================================================================
 *
 *       Filename:  1880.c
 *
 *    Description:  Psych Up's Eigenvalues
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#define NUM 3

int binSearch(int *arr, int len, int to_be_find)
{
    int low = 0; 
    int high = len - 1;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        if(arr[mid] > to_be_find)
            high = mid - 1;
        else if(arr[mid] < to_be_find)
            low = mid + 1;
        else
            return 1;
    }
    return 0;
}

int main(void)
{
    int i,j;
    int *a[NUM];
    int len[NUM];
    int count  = 0;

    for(i = 0; i < NUM; i++)
    {
        scanf("%d", &len[i]);
        a[i] = malloc(len[i] * sizeof(int));
        if(a[i] == NULL)
            return -1;
        for(j = 0; j < len[i]; j++)
            scanf("%d", &a[i][j]);
    }

    for(j = 0; j < len[0]; j++)
    {
        if(binSearch(a[1], len[1], a[0][j]) 
          && binSearch(a[2], len[2], a[0][j]))
            ++count;
    }

    printf("%d\n", count);

    return 0;
}
