/*
 * =====================================================================================
 *
 *       Filename:  slides05-binary-search.c
 *
 *    Description:  binary search
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN(a) (sizeof(a)/sizeof(a[0]))

int binary_search(int *a, int len, int target);
void print_result(int  *a, int len, int target);

int main(void)
{
    int a[] = {1, 3, 5, 7, 8, 9 , 13, 15, 19, 23, 28, 33};
    int target_a[] = {3, 8, 27, 25, 28};

    int i;
    for(i = 0; i < ARR_LEN(target_a); i++)
        print_result(a, ARR_LEN(a), target_a[i]);
    
   return 0; 
}

int binary_search(int *a, int len, int target)
{
    int mid = len / 2;
    if(a == NULL || len <= 0)
        return 0;

    if(len == 1)
        return a[0] == target;

    if(a[mid] == target)
        return 1;

    return binary_search(a, mid, target) || binary_search(&a[mid], len-mid, target);
}

void print_result(int  *a, int len, int target)
{
    int has_target = binary_search(a, len, target);
    if(has_target)
        printf("%d is in array\n",target);
    else
        printf("%d isn't in array\n", target);
}
