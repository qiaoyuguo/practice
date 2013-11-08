/*
 * =====================================================================================
 *
 *       Filename:  test_ex1.c
 *
 *    Description:  ex1 test data generation
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    int i;
    int n = 100;
    int is_first = 1;
    int count = 0;
    srand(time(NULL));
    printf("%d\n",n);
    for(i = 0; i < n; )
    {
        char tmp[3] = {0};
        int c = rand()%4;
        int d = rand()%9 + 1;
        int j;
        sprintf(tmp, "%c%d", c+'A',d);
        if(is_first)
            is_first = 0;
        else 
            printf(" ");
        printf("%s", tmp);
        ++i;
    }
    printf("\n");
    
    return 0;
}
