/*
 * =====================================================================================
 *
 *       Filename:  ex1.cpp
 *
 *    Description:  find two integers whose sum is K
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <iostream>

using namespace std;

int main(void)
{
    int n,k;
    int *a = NULL;
    bool find = false;

    cin >> n >> k;
    a = (int*) malloc(n * sizeof(int));
    if(a == NULL)
        return -1;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n && !find; j++)
        {
            if(a[i] + a[j] == k)
            {
                find = true;
                break;
            }
        }
    }
    if(find)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    free(a);

    return 0;
}
