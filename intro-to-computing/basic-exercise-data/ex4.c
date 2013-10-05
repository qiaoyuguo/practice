/*
 * =====================================================================================
 *
 *       Filename:  ex4.c
 *
 *    Description:  problemID: 1873
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

int swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;

    return 0;
}
/* order=1 means ascending order, order = 0 means descending order */
int compare(int a, int b, int order)
{
    if(order)
        return a > b;
    else
        return a < b;
}
int insert_sort(int a[], int n, int order)
{
    int i,j;
    for(i = 1; i < n; i++)
    {
        int cur_num = a[i];
        for(j = i-1; j >= 0; --j)
            if(compare(a[j] , a[j+1], order))
                swap(&a[j], &a[j+1]);
            else
                break;
    }
    return 0;
}
int main(void)
{
/*  
    int a[] = {1, 8, 2, 7, 3, 5} ;
    int b[] = {1, 8, 2, 7, 3, 5} ;
    int i;
    insert_sort(a, 6, 1);
    insert_sort(b, 6, 0);

    for(i = 0; i < 6; i++)
        printf("%d ", a[i]);
    printf("\n");

    for(i = 0; i < 6; i++)
        printf("%d ", b[i]);
    printf("\n");*/
    int a[10+5] = {0};
    int n = 10;
    while(1)
    {
        int i;
        int cur_num;
        int odd_count = 0; 
        int even_start = 9;
        memset(a, 0, sizeof(a)/sizeof(int));
        if(scanf("%d", &cur_num) == EOF)
            break;
        if(cur_num % 2 != 0) 
            a[odd_count++] = cur_num;
        else
            a[even_start--] = cur_num;
        for(i = 0; i < 9; i++)
        {
            scanf("%d", &cur_num);
            if(cur_num % 2 != 0)
                a[odd_count++] = cur_num;
            else
                a[even_start--] = cur_num;
        }
        /*  
        for(i = 0; i < 10; i++)
            printf("%d ", a[i]);
        printf("\n");*/
        insert_sort(&a[0], odd_count, 0);
        insert_sort(&a[odd_count], 10-odd_count,1 );
          
        
        printf("%d", a[0]);
        for(i = 1; i < 10; i++)
            printf(" %d", a[i]);
        printf("\n");
    }


    return 0;
}
