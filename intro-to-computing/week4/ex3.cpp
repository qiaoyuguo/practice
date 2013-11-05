/*
 * =====================================================================================
 *
 *       Filename:  ex3.cpp
 *
 *    Description:  max score
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <iostream>

using namespace std;

int main(void)
{
    int n;
    int *a;

    cin >> n;
    a = (int*)malloc(n * sizeof(int));
    if(a == NULL)
        return -1;

    for(int i = 0; i < n; i++)
        cin >> a[i];
    int max = a[0];
    for(int i = 1; i < n; i++)
        if(a[i] > max)
            max = a[i];
    free(a);

    cout << max << endl;

    return 0;
}
