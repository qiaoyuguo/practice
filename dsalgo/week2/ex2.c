/*
 * =====================================================================================
 *
 *       Filename:  ex3.c
 *
 *    Description:  basic operation of stack
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 160

char opt[50] = {0};
int main(void)
{
    int count;
    scanf("%d", &count);

    while(count-- > 0)
    {
        int n, *a,cur_num,i, k = 0, has_error=0;
        scanf("%d", &n);
        a = (int*)malloc(N * sizeof(int));
        if(a == NULL)
            return -1;

        for(i = 0; i < n; i++)
        {
            getchar();
            memset(opt, 0, sizeof(opt)/sizeof(char));
            scanf("%s", opt);
            //printf("(%d %s %d)\n",i, opt, cur_num);
            if(strcmp(opt, "push") == 0)
            {
                scanf("%d", &cur_num);
                if(has_error == 0)
                    a[k++] = cur_num; 
            }
            else if(strcmp(opt, "pop") == 0)
            {
                if(has_error == 0)
                    --k;
            }
            if(k < 0)
            {
                has_error = 1;
            }

            //printf("k=%d ",k);
        }
        if(has_error)
            printf("error\n");
        else if(k == 0)
        {}
        else if(k > 0)
        {
            for(i = 0; i < k-1; i++)
                printf("%d ", a[i]);
            printf("%d", a[k-1]);
            printf("\n");
        }
        free(a);
    }

    return 0;
}
