/*
 * =====================================================================================
 *
 *       Filename:  ex6.c
 *
 *    Description:  problemID 1889
 *
 * =====================================================================================
 */
#include <stdio.h>

int handle_num(int n)
{
    int first = 1;
    int count = 0,i;
    int a[3] = {0};
    int b[3] = {3,5,7};

    for(i = 0; i < 3; i++)
        if(n%b[i] == 0)
            a[count++] = b[i];
    if(count == 0)
        return 0;
    printf("%d", a[0]);
    for(i = 1; i< count; i++)
        printf(" %d", a[i]);
    printf("\n");
    return 0;
}
int main(void)
{
   int cur_num;
   while(scanf("%d", &cur_num) != EOF)
   {
       handle_num(cur_num);
   }

   return 0;
}
