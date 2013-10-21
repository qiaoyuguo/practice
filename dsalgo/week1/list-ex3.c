/*
 * =====================================================================================
 *
 *       Filename:  ex3.c
 *
 *    Description:  problemID 5345(bit query)
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_ones(int *a, int n, int bit_idx)
{
    int count = 0,i;
    for(i = 0; i < n; i++)
        if(a[i] & (1<<bit_idx))
            ++count;
    return count;
}
int main(void)
{
    int i,n,m,j;
    int *a;
    char buf[50] = {0};
    scanf("%d %d", &n, &m);
    a = malloc(n * sizeof(int));
    if(a == NULL)
        return -1;
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    fgets(buf, 50, stdin);
    for(i = 0; i < m; i++)
    {
        char operation; 
        int num;
        memset(buf, 0, 50*sizeof(char));
        fgets(buf, 50 , stdin);
        sscanf(buf, "%c %d", &operation, &num);
        //printf("%c %d\n", operation, num);

        if(operation == 'Q')
            printf("%d\n", count_ones(a, n, num ));
        else if(operation == 'C')
        {
            for(j = 0; j < n; j++)
            {
                a[j] = (a[j] + num)%65536;
            }
        }
    }
    free(a);
}
