/*
 * =====================================================================================
 *
 *       Filename:  slides05-merge-sort.c
 *
 *    Description:  merge sort
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR -1
#define OK 0

int init_array(int **a,int len);
int del_array(int **a);
int print_array(int *a, int len);
int merge_sort(int *a, int *assis_a, int len);
int merge(int *a, int mid, int len, int *assis_a);
int alloc_array(int **assis_a, int len);

int main(void)
{
    int *a, len = 20;
    int *assis_a; //assistant array, used for storaging merge data
    int ret = init_array(&a, len);
    printf("print the initial array:\n");
    print_array(a, len);
    alloc_array(&assis_a, len);

    merge_sort(a,assis_a, len);
    printf("after sorting:\n");
    print_array(a, len);
    del_array(&a);


    return 0;
}

int merge_sort(int *a, int *assis_a, int len)
{
    int mid;
    if(a == NULL)
        return ERROR;
    if(len == 1)
    {
        return OK;
    }
    mid = len / 2;
    merge_sort(a, assis_a, mid);
    merge_sort(&a[mid],assis_a,  len-mid);
    merge(a, mid, len, assis_a);
    printf("this round: ");
    print_array(a, len);
    return OK;
}

int merge(int *a, int mid, int len, int *assis_a)
{
    int i,j;
    int count = 0;
    for(i = 0, j = mid; i < mid && j < len; )
    {
        if(a[i] <= a[j])
            assis_a[count++] = a[i++];
        else
            assis_a[count++] = a[j++];
    }
    while(i < mid)
        assis_a[count++] = a[i++];
    while(j < len)
        assis_a[count++] = a[j++];
    for(i = 0; i < len; i++)
    {
        a[i] = assis_a[i];
    }

    return OK;
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
int alloc_array(int **assis_a, int len)
{
    int i;
    if(assis_a == NULL)
        return ERROR;

    *assis_a = malloc(len * sizeof(int));
    if(assis_a == NULL)
        return ERROR;

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

