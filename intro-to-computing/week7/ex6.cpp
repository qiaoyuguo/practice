/*
 * =====================================================================================
 *
 *       Filename:  ex6.cpp
 *
 *    Description:  mid number
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <iostream>

using namespace std;

void bubbleSort(int *a, int n)
{
    int i,j;
    for(i = 0; i < n; i++)
        for(j = n-1; j > i; j--)
            if(a[j] < a[j-1])
            {
                int tmp = a[j];
                a[j] = a[j-1];
                a[j-1] = tmp;
            }
}
int main(void)
{
#if 0
    int i;
    int a[]  = {1,7,4,9,8};
    int n = sizeof(a)/sizeof(int);
    bubbleSort(a, n);
    for(i = 0; i < n; i++)
        cout << a[i] << endl;
#endif
    while(1)
    {
        int n, *a,i;
        cin >> n;
        if(n <= 0)
            break;
        a = (int*)malloc(sizeof(int) *n);
        if(a == NULL)
            return -1;
        for(i = 0; i < n; i++) 
            cin >> a[i];
        bubbleSort(a, n);
        if(n%2 == 0)
            cout << (a[n/2] + a[n/2-1])/2 << endl;
        else
            cout << a[n/2] << endl;
        free(a);
    }
    return 0;
}
