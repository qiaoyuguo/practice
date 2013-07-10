/*
 * =====================================================================================
 *
 *       Filename:  QuickSort.c
 *
 *    Description:  Quick sort
 *
 *        Version:  1.0
 *        Created:  2013年07月10日 09时20分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qiao Yuguo (), qiaoyuguo2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

#define INPUT_FILE "QuickSort.txt"
#define MAX 10000
#define OK 1
#define ERROR -1

int buf[MAX]; 
int total_cmp; // total comparitions

typedef enum {
    FIRST,   //pivot at head postion
    MEDIAN,  //pivot at center position 
    LAST,    // pivot at tail position
    MEDIAN3, // pivot as mininum of head and center and tail
} PIVOT_POS;//Pivot position at head or median or last of array 

void print_arr(int a[], int left, int right)
{
    int i;
    for(i = left; i <= right; i++)
        printf("%d ", a[i]);
    printf("\n");
}


int min2(int a, int b)
{
    return a <= b ? a : b;
}
int get_min3_index(int i, int j, int k, int a, int b, int c)
{
    if( (b <= a && a <= c) || (c <= a && a <= b))
        return i;
    if((a <= b && b <= c) || (c <= b && b <= a))
        return j;
    if( (a <= c && c<= b) || (b <= c && c <= a))
        return k;
}
int prepare_sort(char *file_name, int *buf, int len)
{
    int ret;
    total_cmp = 0;
    memset(buf, 0, len);
    ret = read_file_to_buf(file_name, buf, len);
    if(ret != OK)
    {
        fprintf(stderr, "can't read file %s", INPUT_FILE );
        return ERROR;
    }
    return OK;
}
int read_file_to_buf(char *file, int *buf, int max)
{
    FILE *fp;
    int i;
    fp = fopen(file, "r");
    if(fp == NULL)
        return ERROR;
    for(i = 0; i < max; i++)
    {
        if(fscanf(fp, "%d", &buf[i]) == -1)
            break;
    }
    return OK;
}
void swap_int(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int partition(int a[], int left, int right, PIVOT_POS pos)
{
    int pivot_index, pivot;
    int i,j;
    if(pos == FIRST)
        pivot_index = left;
    else 
    {
        if(pos == MEDIAN)
            pivot_index = (left + right)/2;
        else if(pos == LAST)
            pivot_index = right;
        else if(pos == MEDIAN3)
        {
           int mid = (left+right)/2;
           pivot_index = get_min3_index(left, mid,right,a[left], a[mid] ,a[right]);
           //printf("pivot:%d ", pivot_index);
        }
        swap_int(&a[left], &a[pivot_index]);
    }
    pivot = a[left];
    i = left + 1;
    
    for(j = left + 1; j <= right; j++)
        if(a[j] < pivot)
        {
            swap_int(&a[j], &a[i]);
            ++i;
        }
    total_cmp += right - left;
    swap_int(&a[left], &a[i-1]);
    return i-1;
}
void quick_sort(int a[], int left, int right, PIVOT_POS pos)
{
    int part_pos;
    if(left >= right) 
    {
        //++total_cmp;
        return;
    }

    //++total_cmp;  
    part_pos = partition(a, left, right, pos);
    quick_sort(a, left, part_pos-1, pos);
    quick_sort(a, part_pos + 1, right, pos);
}

void get_result(char *file, int *buf, int len)
{
    printf("statistics for file %s\n", file);
    prepare_sort(file, buf,len);
    quick_sort(buf, 0, len-1, FIRST);
    printf("pivot at first position, comparition is %d\n", total_cmp);
    prepare_sort(file, buf,len);
    quick_sort(buf, 0, len-1, MEDIAN);
    printf("pivot at median position, comparition is %d\n", total_cmp);
    prepare_sort(file, buf,len);
    quick_sort(buf, 0, len-1, LAST);
    printf("pivot at last position, comparition is %d\n", total_cmp);
    prepare_sort(file, buf,len);
    quick_sort(buf, 0, len-1, MEDIAN3);
    printf("pivot at median3(min of first and last and middle) position, comparition is %d\n\n", total_cmp);

}
int test_get_min3_index(void)
{
    printf("%d \n", get_min3_index(1,2,3,1,2,3)); //2
    printf("%d \n", get_min3_index(1,2,3,1,3,2)); //3
    printf("%d \n", get_min3_index(1,2,3,2,1,3)); //1
    printf("%d \n", get_min3_index(1,2,3,2,3,1)); //1
    printf("%d \n", get_min3_index(1,2,3,3,1,2)); //3
    printf("%d \n", get_min3_index(1,2,3,3,2,1)); //2
}
int main(void)
{
#if 0
    int arr[] = {3,9,8,4,6,10,2,5,7,1}; //result should be 25 29 31

    int len = sizeof(arr)/sizeof(arr[0]);
    get_result(arr, len);
    //quick_sort(arr, 0, len-1, FIRST);
    //quick_sort(arr, 0, len-1, MEDIAN);
    //quick_sort(arr, 0, len-1, LAST);
    //quick_sort(arr, 0, len-1, min3);
    //print_arr(arr, 0, len-1);

    test_get_min3_index();
#endif
#if 1
    get_result("10.txt", buf, 10);
    get_result("100.txt", buf, 100);
    get_result("1000.txt", buf, 1000);
    get_result(INPUT_FILE, buf, MAX);

#endif
    return 0;
}
