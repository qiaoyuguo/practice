/*
 * =====================================================================================
 *
 *       Filename:  1496.c
 *
 *    Description:  Spammer
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 35

struct comp
{
    char name[MAX + 5];
    int count;
};

typedef struct comp Comp;

int bin_search(Comp *c, int n, char *name)
{
    int low = 0;
    int high = n -1;
    int mid;

    while(low <= high)
    {
        int ret_val;
        mid = (low + high) / 2;
        ret_val = strcmp(c[mid].name, name);
        if(ret_val == 0)
            return mid;
        else if(ret_val < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}
int main(void)
{
    int n,i;
    Comp *c;
    char buf[MAX + 5];
    int total_comp = 0;
   
    scanf("%d", &n);
    c = malloc(sizeof(Comp) * n);
    if(c == NULL)
        return -1;

    memset(c, 0, sizeof(Comp) * n);
    for(i = 0; i < n; i++)
    {
        int ret_val;
        memset(buf, 0, sizeof(buf));
        scanf("%s", buf);
        ret_val = bin_search(c,total_comp, buf);
        if(ret_val == -1)
        {
            int j,k;
            for(j = total_comp-1; j >= 0; j--)
            {
                if(strcmp(c[j].name, buf) > 0)
                    c[j+1] = c[j];
                else
                    break;
            }
            strcpy(c[j+1].name, buf);
            c[j+1].count = 1;
            total_comp += 1;
#if 0
            for(k = 0; k < total_comp; k++)
            {
                printf("%d %d %s %s\n",j, c[k].count, c[k].name,buf);
            }
            printf("\n");
#endif
        }
        else
        {
            c[ret_val].count++;
        }
    }

    for(i = 0; i < total_comp; i++)
    {
        //printf("%d %s\n", c[i].count, c[i].name);
        if(c[i].count > 1)
            printf("%s\n", c[i].name);
    }

    return 0;
        
}
