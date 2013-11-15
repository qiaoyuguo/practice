/*
 * =====================================================================================
 *
 *       Filename:  ex3.c
 *
 *    Description:  stack or queue
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int count;
    scanf("%d", &count);
    while(count-- > 0)
    {
        int n,i,*a,k=0,has_error = 0;
        int opt,num;
        scanf("%d", &n);
        a = (int*)malloc(n * sizeof(int));
        if(a == NULL)
            return -1;
        for(i = 0; i < n; i++) 
        {
            getchar();
            scanf("%d %d", &opt, &num);
            if(opt == 1)
                a[k++] = num;
            else if(opt == 2)
            {
                if(k > 0 && num != a[--k])
                {
                    has_error = 1;
                }
            }
        }
        if(has_error)
            printf("Queue\n");
        else
            printf("Stack\n");
        free(a);
    }

    return 0;
}
