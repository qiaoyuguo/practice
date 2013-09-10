/*
 * =====================================================================================
 *
 *       Filename:  1196.c
 *
 *    Description:  History Exam
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bin_search(int a[], int n, int target)
{
    int low = 0;
    int high = n - 1;
    int mid;

    while(low <= high)
    {
        mid = (low + high)/2;
        if(a[mid] == target)
            return mid;
        else if(a[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}
int main(void)
{
    int prof_input_n = 0;
    int prof_real_n = 0;
    int stud_input_n = 0;
    int stud_real_n = 0;
    int i;
    int *prof = NULL;
    int *stud = NULL;
    int *count = NULL;
    int sum = 0;

    scanf("%d", &prof_input_n);
    prof = malloc(sizeof(int) * prof_input_n);
    if(prof == NULL)
        return -1;
    for(i = 0; i < prof_input_n; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        if(prof_real_n == 0 ||  tmp != prof[prof_real_n-1])
        {
            prof[prof_real_n++] = tmp;
        }
    }
#if 0
    for(i = 0; i < prof_real_n; i++)
    {
        printf("%d ", prof[i]);
    }
    printf("\n");
#endif
    count = malloc(sizeof(int) * prof_real_n);
    if(count == NULL)
    {
        free(prof);
        return -1;
    }
    memset(count, 0, sizeof(int) * prof_real_n);
#if 1
    scanf("%d", &stud_input_n);
    stud = malloc(sizeof(int) * stud_input_n);
    if(stud == NULL)
    {
        free(prof);
        free(count);
        return -1;
    }
    memset(stud, 0, sizeof(int)*stud_input_n);
    for(i = 0; i < stud_input_n; i++)
    {
        int tmp;
        int ret_val;
        scanf("%d", &tmp);
        ret_val = bin_search(prof, prof_real_n, tmp);
        if(ret_val != -1)
        {
            ++count[ret_val];
            sum += 1;
        }
    }

#endif
    if(prof != NULL)
        free(prof);
    if(stud != NULL)
        free(stud);
    if(count != NULL)
        free(count);

    printf("%d\n", sum);

    return 0;
}
