/*
 * =====================================================================================
 *
 *       Filename:  1243.c
 *
 *    Description:  Divorce of the Seven Dwarfs
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    char buf[60] = {0};
    int len,i, result = 0;

    scanf("%s", buf);
    len = strlen(buf);
    for(i = 0; i < len; i++)
    {
        result = 10*result +  (buf[i] - '0');
        result %= 7;
    }

    printf("%d\n", result);

    return 0;
    
}
