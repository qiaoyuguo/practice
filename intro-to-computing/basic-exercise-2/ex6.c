/*
 * =====================================================================================
 *
 *       Filename:  ex6.c
 *
 *    Description:  problemID: 1689 
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n,i;
    int *a = NULL;
    int first = 1;

    scanf("%d", &n);

    a = malloc(sizeof(int) * n);
    if(a == NULL)
        return  -1;
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(i = n-1; i >= 0; i--)
    {
        if(first)
        {
           first = 0; 
        }
        else
        {
            printf(" ");
        }
        printf("%d", a[i]);
    }
    printf("\n");

    free(a);
    return 0;
}
