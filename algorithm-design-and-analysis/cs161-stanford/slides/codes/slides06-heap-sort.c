/*
 * =====================================================================================
 *
 *       Filename:  slides06-heap-sort.c
 *
 *    Description:  heap sort
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR   -1

int init_array(int **a,int len);
int del_array(int **a);
int print_array(int *a, int len);
int heap_sort(int *a, int len);
int heapify(int *a, int len,  int i, int n);
int swap(int *a, int *b);
int sink(int *a, int len);

int main(void)
{
    int *a, len = 10;
#if 0
    int b[] = {1,2,3,9,15,22,3,5,8,14};
    a = b;
#endif
    init_array(&a, len);
    print_array(a, len);
    heap_sort(a, len);
    print_array(a, len);

    return 0;
}
int heap_sort(int *a, int len)
{
    int i;
    if(a == NULL)
        return ERROR;

    for(i = 0; i < len; i++)
    {
        //sink(a, i);
        heapify(a, i+1, i, a[i]);
    }

    for(i = len-1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
        sink(a, --len);
    }

    return OK;
}

int sink(int *a, int len)
{
    int i;

    if(a == NULL || len < 0)
        return ERROR;

    int max_index = 0;
    for(i = 0; i < len; i =  max_index)
    {
        int left_index = 2 * max_index + 1;
        if(left_index < len && a[max_index] < a[left_index])
        {
            max_index = left_index;
        }
        if(left_index+1 < len && a[max_index] < a[left_index+1])
            max_index = left_index + 1;
        if(max_index != i)
            swap(&a[max_index], &a[i]);
        else 
            break;
        //printf("max index:%d, i:%d,len:%d\n", max_index, i,len);
        //print_array(a, len);
    }

    return OK;
}
int heapify(int *a, int len,  int i, int n)
{
    int j;
    if(a == NULL || i >= len || i < 0)
        return ERROR;
    
    for(j = i; j >= 0; j = (j-1)/2)
    {
        int parent_index = (j-1)/2;
        int max_index = parent_index;
        if(parent_index * 2+1< len && a[max_index] < a[parent_index*2+1])
            max_index = parent_index*2+1;
        if(parent_index*2 + 2 < len
          && a[max_index] < a[parent_index*2 + 2] )
            max_index  = parent_index*2 + 2;
        if(max_index == parent_index)
            break;
        if(max_index != parent_index)
            swap(&a[max_index], &a[parent_index]);
        //printf("max:%d,parent_index:%d\n",max_index, parent_index );
        //print_array(a,len);
    }
    return OK;
}

int swap(int *a, int *b)
{
    int tmp;
    if(a == NULL || b == NULL)
        return ERROR;
    tmp = *a;
    *a = *b;
    *b = tmp;

    return OK;
}
#if 0
int get_max_index(a, len, i, n)
{
    int parent_index = i/2;
    int max_index = i;
    if(a == NULL || i >= len || i <= 0)
        return ERROR;
    if(a[parent_index] > a[max_index] ) 
        max_index = parent_index;
     
}
#endif

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

