/*
 * =====================================================================================
 *
 *       Filename:  2_5.cpp
 *
 *    Description:  inverse array
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    int n,i;
    int *a = NULL;
    bool first = true;

    cin >> n;
    a = (int*)malloc(sizeof(int) * n);
    if(a == NULL)
        return -1;
    for(i = 0; i < n; i++)
        cin >> a[i];
    for(i = n-1;i >= 0; i--)
    {
        if(first)
            first = false;
        else
            cout << " ";
        cout << a[i];
    }
    cout << endl;
    free(a);

    return 0;
}
