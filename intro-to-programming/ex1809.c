/*
 * =====================================================================================
 *
 *       Filename:  ex1809.c
 *
 *    Description:  1809
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
int main(void)
{
    unsigned long long a, b;
    unsigned long long r;
    int count = 0;
    char c[20] = {0};
    char d[20] = {0};
    int i,len1, len2;

    scanf("%llu%llu", &a, &b);
    sprintf(c, "%llu", a);
    sprintf(d, "%llu", b);

    len1 = strlen(c);
    len2 = strlen(d);
    for(i = 0; i < len1;)
    {
        char *res = strstr(c+i, d);
        if(res == NULL)
            break;
        else
        {
            /*  printf("%s,i=%d\n", res, i);*/
            i = res-c+1;
            /*  printf("%s,i=%d\n\n", c+i, i);*/
            ++count;
        }
    }

    printf("%d\n", count);

    return 0;
}


