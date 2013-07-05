/*
 * =====================================================================================
 *
 *       Filename:  closest-pair.c
 *
 *    Description:  compute closest pair
 *
 *        Version:  1.0
 *        Created:  2013年07月05日 16时17分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qiao Yuguo (), qyg@homewell.com.cn
 *        Company:  
 *
 * =====================================================================================
 */
/*  use algorithm from http://cgi.csc.liv.ac.uk/~ped/teachadmin/algor/d_and_c.html */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define EPISLON 1e-7
typedef struct point_s{
    double x;
    double y;
}point;

double closest_split_pair(point *array,int mid, int len, double min);
int is_less_than(double x, double y)
{
    return x-y <-EPISLON;
}
double square(double x)
{
    return x*x;
}
double distance(point *p1, point *p2)
{
    int x1 = p1->x;
    int y1 = p1->y;
    int x2 = p2->x;
    int y2 = p2->y;
    return sqrt(square(x2-x1) + square(y2-y1));
}

//point sorted array(x is in ascending order, if not sorted, may use qsort to sort it to satisfy requirement) whose element number is len
double closest_pair(point *array, int len)
{
    double left_min, right_min;
    int mid;
    double min;
    double split_min;
    if(len == 2)
    {
        return distance(&array[0], &array[1]);
    }
    else if(len == 3)
    {
        min = distance(&array[0], &array[1]);
        double dist12 = distance(&array[1], &array[2]);
        double dist02 = distance(&array[0], &array[2]);
        if(is_less_than(dist12, min))
            min = dist12;
        if(is_less_than(dist02, min))
            min = dist02;
        return min;
    }
    mid = len/2;
    left_min = closest_pair(array, mid);
    right_min = closest_pair(&array[mid], len-mid);
    min = is_less_than(left_min, right_min)?left_min:right_min;
    //printf("%.3f %.3f ", left_min, right_min);
    split_min = closest_split_pair(array, mid, len, min);
    return is_less_than(min,split_min)?min:split_min;
}

double closest_split_pair(point *array,int mid, int len, double min)
{
    int left_boundary, right_boundary; 
    int i,j;
    for(left_boundary = 0; left_boundary < mid; left_boundary++)
        if(is_less_than(array[mid].x - min/2 , array[left_boundary].x))
            break;

    for(right_boundary = len-1; right_boundary >= mid; right_boundary--)
        if(is_less_than(array[right_boundary].x, array[mid].x + min/2))
            break;
    
    for(i = left_boundary; i < mid; i++)
        for(j = mid; j <= right_boundary; j++)
            if(is_less_than(distance(&array[i],&array[j]), min))
                min = distance(&array[i], &array[j]);
    return min;
}

// brute force  method to find the closest pair
double brute_closest_pair(point *array, int len)
{
    int i;
    int j;

    double min = INT_MAX;
    for(i = 0; i < len; i++)
        for(j = i+1; j < len; j++ )
        {
            double cur_dist= distance(&array[i], &array[j]);
            //printf("%d,%d,%.3f ",i,j, cur_dist);
            if(cur_dist < min)
                min = cur_dist;
        }
    return min;
}
int main(void)
{
    point array[] = {{1,2}, {3,5}, {6,8}, {7, 9}};
    int len = sizeof(array)/sizeof(array[0]);
#if 0
    int i,j;
    for(i = 0; i < len;i++)
        for(j = i+1; j < len; j++)
            printf("%.3f ", distance(&array[i], &array[j]));
    printf("\n");
#endif
    printf("%.3f\n", closest_pair(array, len));
    printf("%.3f\n", brute_closest_pair(array, len));

    return 0;
}
