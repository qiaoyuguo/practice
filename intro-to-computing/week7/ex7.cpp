/*
 * =====================================================================================
 *
 *       Filename:  ex6.cpp
 *
 *    Description:  shift move
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <iostream>

using namespace std;

int rightShiftOne(int *a, int n)
{
    int i;
    int tmp = a[n-1];
    for(i = n-1; i >= 1; i--)
        a[i] = a[i-1];
    a[0] = tmp;

    return 0;
}
int main(void)
{
    int n,m,i;
    int *a;

    cin >>n >>m;
    a = (int*)malloc(n*sizeof(int));
    if(a == NULL)
        return -1;
    for(i = 0; i < n; i++)
        cin >> a[i];
    for(i = 0; i < m%n; i++)
        rightShiftOne(a,n);
    
    for(i = 0; i < n; i++)
        cout <<  a[i] << ' ';
    cout << endl;
    free(a);

    return 0;
}
