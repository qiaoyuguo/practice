/*
 * =====================================================================================
 *
 *       Filename:  slides07-max-value.c
 *
 *    Description:  find max value in an array
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define ERROR -1

int init_array(int **a,int len);
int del_array(int **a);
int print_array(int *a, int len);
int find_max_value(int *a, int len);
int max(int a, int b);

int main(void)
{
    int len = 10;
    int *a;

    int ret = init_array(&a, len);
    printf("print the initial array:\n");
    print_array(a, len);
    printf("max value is %d\n", find_max_value(a, len));
    del_array(&a);

    return 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int find_max_value(int *a, int len)
{
    int i,j;    
    int *ass; 
    int range = len;
    int ass_len = len/2;
    int max_value;
    if(len == 1)
        return a[0];
    if(range % 2 != 0)
    {
        range -= 1;
        ass_len += 1;
    }

    ass = malloc(ass_len * sizeof(int));
    if(ass == NULL)
        return ERROR;
    memset(ass, 0, ass_len * sizeof(int));
    for(i = 0,j = 0; i < range; i+=2)
        ass[j++] = max(a[i], a[i+1]);
    if(range ==  len - 1)
        ass[j++] = a[range];
    max_value = find_max_value(ass, ass_len);
    del_array(&ass);
    return max_value;
}

int init_array(int **a,int len)
{
    int i;
    if(a == NULL)
        return ERROR;
    srandom(time(NULL));
    *a = malloc(len * sizeof(int));
    if(*a == NULL)
        return ERROR;
    memset(*a, 0, len * sizeof(int));
    for(i = 0; i < len; i++)
        (*a)[i] = random() % 100;
    return OK;
}
int del_array(int **a)
{
    if(a == NULL || *a == NULL)
        return ERROR;

    free(*a);
    *a = NULL;

    return OK;

}

int print_array(int *a, int len)
{
    int i;

    if(a == NULL || len <= 0)
        return ERROR;

    printf("%d", a[0]);
    for(i = 1; i < len; i++)
    {
        printf(" %d", a[i]);
    }

    printf("\n");

    return OK;
}

