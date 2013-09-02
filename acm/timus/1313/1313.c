/*
 * =====================================================================================
 *
 *       Filename:  1313.c
 *
 *    Description:  Some Words about Sport
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

void print_arr(int **arr, int n)
{
    int i = 0,j = 0,k;
    printf("%d", arr[0][0]);
    while(i != n-1 || j != n-1)
    {
        int cur_num;
        int up = 0;
        if(i == 0)
        {
            ++i;
            up = 0;
        }
        else if(j == 0)
        {
            ++j;
            up = 1;
        }
        up = ~up;
        cur_num = i + j;
        if(cur_num > n)
            cur_num = 2*n-2-cur_num;
        for(k = 0; k <= cur_num; k++)
        {
            if(up)
            {
                --i;
                ++j;
            }
            else
            {
                ++i;
                --j;
            }
            printf(" %d", arr[i][j]);
        }
    }
    printf(" %d\n", arr[n-1][n-1]);
}
int main(void)
{
    int **arr;
    int n;
    int i,j;

    scanf("%d", &n);
    arr = malloc(n * sizeof(int*));
    if(arr == NULL)
        return -1;
    for(i = 0; i < n; i++)
        arr[i] = malloc(n * sizeof(int));

    for(i = 0; i < n; i++)
    {
        for(j = 0;j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    print_arr(arr, n);

    for(i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}
