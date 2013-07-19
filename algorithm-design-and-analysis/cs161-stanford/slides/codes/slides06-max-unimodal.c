/*
 * =====================================================================================
 *
 *       Filename:  slides06-max-unimodal.c
 *
 *    Description:  find max element  of an unimodal array
 *                 an array is unimodal if and only if it can be splitted into increasing sequence followed by a decreasing sequence 
 *
 *    note: this algorithm seemed to be a buggy algorithm
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR -1
#define ARR_LEN(a) (sizeof(a)/sizeof(a[0]))

int max_unimodal(int *a, int len);
void print_result(int *a, int len);
int max_weak_unimodal(int *a, int len);
int max(int a, int b);

int main(void)
{
    int a[] = {1, 2, 8, 9, 15, 18, 22, 35, 24, 21, 15};
    int b[] = {1, 2, 8, 9, 15, 17, 18, 19, 24, 28, 15};
    int c[] = {1, 2, 8, 9, 15, 17, 18, 19, 24, 28, 15, 12, 10};
    //int b[] = { 1, 2, 5, 7, 3, 8, 9, 10, 15, 20, 14 ,17, 21, 23, 13, 7};
    int i;

    print_result(a, ARR_LEN(a));
    print_result(b, ARR_LEN(b));
    print_result(c, ARR_LEN(c));

    return 0;
}
void print_result(int *a, int len)
{
    printf("max unimodal is %d\n", max_unimodal(a, len));
    printf("max weak unimodal element is %d\n", max_weak_unimodal(a, len));
}

int max_unimodal(int *a, int len)
{
    int mid;

    if(a == NULL || len <= 0)    
        return ERROR;
    if(len <= 2)
        return a[len - 1];

    mid = len / 2;
    if(a[mid] < a[mid + 1])
        return max_unimodal(&a[mid+1], len-mid - 1);
    else
        return max_unimodal(a, mid+1);

    return OK;
}
int max_weak_unimodal(int *a, int len)
{
    int mid;

    if(a == NULL || len <= 0)    
        return ERROR;
    if(len <= 2)
        return a[len - 1];

    mid = len / 2;
    if(a[mid] < a[mid + 1])
        return max_weak_unimodal(&a[mid+1], len-mid - 1);
    else if(a[mid > a[mid + 1]])
        return max_weak_unimodal(a, mid+1);
    else
        return max(max_weak_unimodal(&a[mid+1], len-mid - 1),max_weak_unimodal(a, mid+1));

    return OK;
}

int max(int a, int b)
{
    return a > b ? a : b;
}
