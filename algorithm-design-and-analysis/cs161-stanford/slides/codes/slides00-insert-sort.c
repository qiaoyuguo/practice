/*
 * =====================================================================================
 *
 *       Filename:  slides00-insert-sort.c
 *
 *    Description:  insert sort
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define ERROR -1

void insert_sort(int a[], int len);
int init_array(int **a,int len);
int del_array(int **a);
int print_array(int *a, int len);

int main(int argc, char *argv)
{
    int len = 10;
    int *a;

    int ret = init_array(&a, len);
    print_array(a, len);
    insert_sort(a, len);
    print_array(a, len);
    del_array(&a);

    return 0;
}

void insert_sort(int a[], int len)
{
    int i,j;
    for(i = 0; i < len; i++)
    {
        int cur_elem = a[i];
        for(j = i-1; j >= 0; j--)
            if(a[j] > cur_elem)
                a[j + 1] = a[j];
        a[j + 1] = cur_elem;
        print_array(a, len);
    }
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

