/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  solution of counting invertion number in an array
 *
 *        Version:  1.0
 *        Created:  2013年07月05日 09时08分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qiao Yuguo (), qiaoyuguo2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
/*  
file "IntegerArray.txt" contains all of the 100,000 integers between 1 and 100,000 (inclusive) in some order, with no integer repeated.

Your task is to compute the number of inversions in the file given, where the ith row of the file indicates the ith entry of an array.
Because of the large size of this array, you should implement the fast divide-and-conquer algorithm covered in the video lectures. The numeric answer for the given input file should be typed in the space below.
So if your answer is 1198233847, then just type 1198233847 in the space provided without any space / commas / any other punctuation marks. You can make up to 5 attempts, and we'll use the best one for grading.
(We do not require you to submit your code, so feel free to use any programming language you want --- just type the final numeric answer in the following space.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_NUM 100000
#define DATA_FILE "IntegerArray.txt"

long long count_split_invertion(int *array, int fst_ndx, int mid_ndx, int last_ndx);
long long count_invertion(int *array, int fst_ndx, int last_ndx);
void print_array(int *array, int fst, int last);
int read_file_to_array(char *file_name, int *array, int len);

int buf[TOTAL_NUM] = {0};
int array[TOTAL_NUM] = {0};

// read integers from file to array
int read_file_to_array(char *file_name, int *array, int len)
{
    FILE *fp = NULL;
    int i;
    fp = fopen(file_name, "r");
    if(fp == NULL)
        return -1;
    for(i = 0; i < len; i++)
        fscanf(fp, "%d",&array[i]);
    fclose(fp);
    return 0;
}

// count all the invertions in array from index of fst_ndx to last_ndx
long long count_invertion(int *array, int fst_ndx, int last_ndx)
{
    long long left_count,right_count,split_count;
    int mid_ndx;
    if(fst_ndx >= last_ndx)
        return 0;
    mid_ndx = (fst_ndx + last_ndx)/2;
    //count invertions of the left array
    left_count = count_invertion(array, fst_ndx, mid_ndx);
    //count invertions of the right array
    right_count = count_invertion(array, mid_ndx+1, last_ndx);
    //count invertions between numbers of left and right array
    split_count = count_split_invertion(array, fst_ndx, mid_ndx, last_ndx);

    return left_count + right_count + split_count;
}

// merge the left and right array and count corresponding invertions
long long count_split_invertion(int *array, int fst_ndx, int mid_ndx, int last_ndx)
{
    int i,j,k = 0;
    long long count = 0;

    memset(buf, 0, sizeof(buf));
    i = fst_ndx;
    j = mid_ndx+1;
    while(i <= mid_ndx && j <= last_ndx )
    {
        if(array[i] < array[j])
            buf[k++] = array[i++];
        else
        {
            buf[k++] = array[j++];
            count += mid_ndx - i + 1;
        }
    }
    while(i <= mid_ndx)
        buf[k++] = array[i++];
    while(j <= last_ndx)
        buf[k++] = array[j++];
    for(i = fst_ndx,k=0; i <= last_ndx;i++)
    {
        array[i] = buf[k++];
    }
    return count;
}

void print_array(int *array, int fst, int last)
{
    int i;
    for(i = fst; i <= last; i++)
        printf("%d ", array[i]);
    printf("\n");
}
int main(void)
{
    if(read_file_to_array(DATA_FILE, array, TOTAL_NUM) != 0)
    {
        fprintf(stderr, "can't read number from file %s",DATA_FILE );
        return -1;
    }
    printf("%lld\n", count_invertion(array, 0, TOTAL_NUM-1));

    return 0;
}
