/*
 * =====================================================================================
 *
 *       Filename:  ex2.c
 *
 *    Description:  problemID: 1936 (insert string to another string
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

int find_max_idx(char *a)
{
    int len,i, max_idx;
    if(a == NULL || strcmp(a, "") == 0) 
        return -1;
    len = strlen(a);
    max_idx = 0;
    if(len == 1)
        return max_idx;
    for(i = 0; i < len; i++)
        if(a[i] > a[max_idx])
            max_idx = i;
    return max_idx;
}
int main(void)
{
    char buf[50] = {0};
    char str[20] = {0};
    char substr[3+1] =  {0};
    int max_idx,i,len;

    while(fgets(buf, 50, stdin) != NULL)
    {
        sscanf(buf, "%s %s", str, substr);
        max_idx = find_max_idx(str);
        if(max_idx < 0)
            return -1;

        for(i = 0; i <= max_idx; i++)
            printf("%c",str[i]);
        printf("%s", substr);
        len = strlen(str);
        for(; i < len;i++)
            printf("%c", str[i]);
        printf("\n");
    }
    return 0;
}
