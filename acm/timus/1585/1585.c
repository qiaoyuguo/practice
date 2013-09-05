/*
 * =====================================================================================
 *
 *       Filename:  1585.c
 *
 *    Description:  Penguins
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int i,j, n;
    int max = 0, maxindex;
    char *s[] = {"Emperor Penguin", "Macaroni Penguin", "Little Penguin"};
    int count[3] = {0};
    char buf[50] = {0};

    scanf("%d", &n);
    fgets(buf, 50, stdin);//skip '\n'
    //printf("buf = %s\n", buf);
    for(i = 0; i < n; i++)
    {
        memset(buf, 0, sizeof(buf));
        fgets(buf, 50, stdin);
        buf[strlen(buf) - 1] = '\0';
        //printf("buf = %s\n", buf);
        for(j = 0; j < 3; j++)
        {
            if(strcmp(buf, s[j]) == 0)
            {
                ++count[j];
                break;
            }
        }
    }
    
    for(i = 0; i < 3; i++)
    {
        if(max < count[i])
        {
            max = count[i];
            maxindex = i;
        }
    }
    printf("%s\n", s[maxindex]);

    return 0;
}
