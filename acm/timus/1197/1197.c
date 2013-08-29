/*
 * =====================================================================================
 *
 *       Filename:  1197.c
 *
 *    Description:  Lonesome Knight
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_valid(int i,int j)
{
    if(i < 1 || j < 1 || i > 8 || j > 8)
        return 0;
    else
        return 1;
}
int handle()
{
    char arr[10]  = {0};
    int tbl[8][2] = {{1,2}, {1,-2}, {2,-1}, {2,1}, {-1,2}, {-1,-2}, {-2,1}, {-2,-1}};
    int i,j,k;
    int count = 0;

    scanf("%s", arr);

    if(strlen(arr) != 2)
       return -1;
    i = arr[0] - 'a' + 1;
    j = arr[1] - '0';

    for(k = 0; k < 8; k++)
    {
        if(is_valid(i+tbl[k][0], j+tbl[k][1]))
        {
            //printf("%d %d\n", i+tbl[k][0], j+tbl[k][1]);
            ++count;
        }
    }

    return count;
}

int main(void)
{
    int i;
    int n;

    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        printf("%d\n", handle());
    }

    return 0;

}
