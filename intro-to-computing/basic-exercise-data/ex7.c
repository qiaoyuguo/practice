/*
 * =====================================================================================
 *
 *       Filename:  ex7.c
 *
 *    Description:  problemID 6176
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
    int no;
    double score;
};

int double_compare(const void *p, const void *q)
{
    struct student *s1 = (struct student *)p;
    struct student *s2 = (struct student *)q;
    if(fabs(s1->score - s2->score ) < 1e-7)
        return 0; 
    else if(s1->score > s2->score)
        return -1;
    else if(s1->score < s2->score)
        return +1;
}
int main(void)
{
    int n, k;
    struct student *a = NULL;
    int i;
    scanf("%d %d", &n, &k);

    a = malloc(sizeof(struct student) * n);
    if(a == NULL)
        return -1;

    for(i = 0; i < n; i++) 
    {
        scanf("%d %lf", &a[i].no, &a[i].score);
    }

    qsort(a,n,sizeof(struct student), double_compare);

    /*
    for(i = 0; i < n; i++)
        printf("%d %g\n", a[i].no, a[i].score);
    printf("%d\n", double_compare((void*)&a[0], (void*)&a[1]));
    k=1;
    */
    printf("%d %g\n", a[k-1].no, a[k-1].score);

    free(a);

    return 0;
}
