/*
 * =====================================================================================
 *
 *       Filename:  ex3.cpp
 *
 *    Description:  find the kth largest number
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <iostream>

using namespace std;

int swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
int main(void)
{
    int n,k, *a;

    cin >> n >> k;
    a = (int*)malloc(sizeof(int) * n);
    if(a == NULL)
        return -1;

    for(int i = 0; i < n; i++)
        cin >> a[i];

    for(int i = 0; i < k; i++)
    {
        int max = a[i];
        int max_index = i;
        for(int j = i+1; j < n; j++)
        {
           if(max < a[j]) 
           {
               max = a[j];
               max_index = j;
           }
        }
        swap(&a[i], &a[max_index]);
    }
    cout << a[k-1] << endl;
    free(a);

    return 0;
}
