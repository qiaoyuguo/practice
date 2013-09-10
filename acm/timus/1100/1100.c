/*
 * =====================================================================================
 *
 *       Filename:  1100.c
 *
 *    Description:  Final standings
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct team
{
    int id;//team id
    int n; //num of problems
};
typedef struct team Team;
Team * assis; //assistant array

void merge(Team a[], int mid, int n)
{
    int i = 0,j = mid, k=0;
    while(i < mid && j < n)
    {
        if(a[i].n >= a[j].n)
            assis[k++] = a[i++];
        else
            assis[k++] = a[j++];
    }
    while(i < mid)
    {
        assis[k++] = a[i++];
    }

    while(j < n)
        assis[k++] = a[j++];

    for(i = 0; i < k; i++)
        a[i] = assis[i];
    
}
void merge_sort(Team a[], int n)
{
    int mid;
    if(n == 1)
        return;
    mid = n/2; 
    merge_sort(a, mid);
    merge_sort(&a[mid], n - mid);
    merge(a, mid, n);
}
#if 0
int team_cmp(const void *t1, const void *t2)
{
    Team *tmp1 = (Team *)t1;
    Team *tmp2 = (Team *)t2;
    return tmp1->n < tmp2->n;
}
#endif
int main(void)
{
    int n,i,j;
    Team *t;

    scanf("%d", &n);
    t = malloc(sizeof(Team) * n);
    if(t == NULL)
        return -1;
    assis = malloc(sizeof(Team) * n);
    if(assis == NULL)
        return -1;
    for(i = 0; i < n; i++)
    {
        scanf("%d %d", &(t[i].id), &(t[i].n));
    }

#if 0
    for(i = n-1; i >= 0; i--)
        for(j = 0; j < i; j++)
        {
            if(t[j].n < t[j+1].n)
            {
                Team tmp = t[j];
                t[j] = t[j+1];
                t[j+1] = tmp;
            }
        }
    // do not use qsort, as it need the same sorted list as bubble sort
    // (which is stable, can only use mergesort)
    qsort(&t[0], n, sizeof(t[0]), team_cmp);
#endif
    merge_sort(t, n);
    for(i = 0; i < n; i++)
    {
        printf("%d %d\n", t[i].id, t[i].n);
    }

    free(t);
    free(assis);

    return 0;
}
