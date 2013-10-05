/*
 * =====================================================================================
 *
 *       Filename:  ex5.c
 *
 *    Description:  problemID 6178
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int group;
    scanf("%d", &group);
    while(group-- > 0)
    {
        int n, *a,i, count = 0,j, found = 0;
        scanf("%d", &n);
        a = malloc(n * sizeof(int));
        if(a == NULL)
            return -1;
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
        
        for(i = 0; i < n && !found; i++)
        {
            for(j = 0; j < i && !found; j++)
            {
                if(a[j] == a[i])
                    ++count;
                if(count == 2)
                {
                    found = 1;
                    break;
                }
            }
            if(found)
                break;
        }
        if(found)
            printf("%d\n", a[i]);
        else
            printf("NOT EXIST\n");
        free(a);
    }

    return 0;
}
