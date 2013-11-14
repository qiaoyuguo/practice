/*
 * =====================================================================================
 *
 *       Filename:  ex1.c
 *
 *    Description:  LightHouse
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Point_S{
    long x;
    long y;
}Point;

#if 0
long canLight(Point *p, Point *q)
{
    if(p->x > q->x && p->y > q->y)
        return 1;
    if(p->x < q->x && p->y < q->y)
        return 1;
    return 0;
}
#endif
long long merge(long *a, long start, long mid, long end, long *temp_arr)
{
    long i=start;
    long j= mid;
    long k = start;
    long long total = 0;
    while(i<= mid && j<= end)
    {
       if(a[i] <= a[j]) 
       {
           temp_arr[k++] = a[i++];
       }
       else
       {
           temp_arr[k++] = a[j++];
           total += mid - i;
       }
    }

    while(i <= mid)
        temp_arr[k++] = a[i++];
    while(j <=  end)
        temp_arr[k++] = a[j++];
    for(i = start; i <= end; i++)
        a[i] = temp_arr[i];

    return total;
}
long long assMergeSort(long *a, long start, long end, long *tmp_arr)
{
    long long total = 0;
    if(start < end)
    {
        long mid = (start+end)/2;
        total = assMergeSort(a, start, mid, tmp_arr);
        total += assMergeSort(a, mid+1, end, tmp_arr);
        total += merge(a, start, mid+1, end, tmp_arr);
    }
    return total;
}
long long mergeSort(long *a, long n)
{
    long *temp = (long*)malloc(sizeof(long) * n);
    long long total;
    if(temp == NULL)
        return 0;
    total =assMergeSort(a, 0, n-1, temp);
    /* free(temp); */
    return total;
}
int cmpLong(const void *p, const void *q)
{
    Point *a = (Point*)p;
    Point *b = (Point*)q;
    if(a->x > b->x)
        return 1;
    else if(a->x == b->x)
        return 0;
    else
        return -1;
}
long main(void)
{
    long n,i,j;
    long long total =0;
    Point *pt;
    long *a, *tmp_arr;
    
    scanf("%ld", &n);
    pt = (Point*)malloc(n * sizeof(Point));
    if(pt == NULL)
        return -1;

    for(i = 0; i < n; i++)
    {
        scanf("%ld %ld", &(pt[i].x), &(pt[i].y));
    }
    qsort(pt, n, sizeof(Point), cmpLong);
#if 0
    for(i = 0; i < n; i++)
    {
        prlongf("(%d,%d)", pt[i].x, pt[i].y);
    }
#endif

    a = (long*)malloc(n * sizeof(long));
    if(a == NULL)
    {
        free(pt);
        return -1;
    }

    for(i = 0; i < n; i++)
    {
        a[i] = pt[i].y;
    }
    free(pt);
    total = (n*(n-1))/2;
    printf("%lld\n", total - mergeSort(a, n));
    free(a);

    return 0;
}
