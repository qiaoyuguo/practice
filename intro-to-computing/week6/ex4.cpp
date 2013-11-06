/*
 * =====================================================================================
 *
 *       Filename:  ex4.cpp
 *
 *    Description:  find two elements whose sum is k
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <iostream>

using namespace std;

int main(void)
{
    int n,k;
    int *a;
    bool is_find = false;

    cin >> n >> k;
    a = (int*)malloc(sizeof(int) * n);
    if(a == NULL)
        return -1;
    for(int i = 0; i < n; i++)
        cin >> a[i];

    for(int i = 0; i < n && !is_find; i++)
        for(int j = i+1; j <n; j++)
        {
            if(a[i]+a[j] == k)
            {
                is_find = true;
                break;
            }
        }
    if(is_find)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    free(a);

    return 0;
}
