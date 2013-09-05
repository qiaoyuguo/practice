/*
 * =====================================================================================
 *
 *       Filename:  1581.c
 *
 *    Description:  Teamwork
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stat
{
   int num;
   int count;
};
typedef struct stat Stat;

int main(void)
{
    int n, m, i = 0;
    Stat *a = NULL;
    scanf("%d", &n);

    a = malloc(sizeof(Stat) * n);
    if(a == NULL)
        return -1;

    memset(a, 0, sizeof(Stat) * n);
    while(scanf("%d", &m) == 1)
    {
        if(a[i].num == 0)
        {
           a[i].num = m;
           ++a[i].count;
        }
        else if(a[i].num == m)
            ++a[i].count;
        else
        {
           ++i;
           a[i].num = m;
           ++a[i].count;
        }
    }
    m = i;
    for(i = 0; i <= m; i++)
    {
        printf("%d %d ", a[i].count, a[i].num);
    }
    printf("\n");

    return 0;
    free(a);
}
