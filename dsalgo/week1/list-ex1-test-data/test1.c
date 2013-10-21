/*
 * =====================================================================================
 *
 *       Filename:  test1.c
 *
 *    Description:  test1
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 3 
#define MAXC

int main(void)
{
    int n = 1;
    int count = 8;
    int i;

    srandom(time(NULL));
    printf("1 \n");
    for(i  = 0; i < count; i++)
    {
        printf("%ld %ld ", random()%100-50, random()%MAX);
    }
    printf("-1 -1\n");
    for(i  = 0; i < count; i++)
    {
        printf("%ld %ld ", random()%100-50, random()%MAX);
    }
    printf("-1 -1\n");

    return 0;

}
