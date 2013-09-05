/*
 * =====================================================================================
 *
 *       Filename:  1263.c
 *
 *    Description:  Electrons
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int n,m,i;
    int *a;
    scanf("%d %d", &n, &m);

    a = malloc(sizeof(int) * n);
    if(a == NULL)
        return -1;
    memset(a, 0, sizeof(int)*n);
    for(i = 0; i < m; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        ++a[tmp-1];
    }
    for(i = 0; i < n; i++)
    {
        printf("%.2f%c\n", 100 * a[i]/(double)m,'%');
    }

    return 0;
}
