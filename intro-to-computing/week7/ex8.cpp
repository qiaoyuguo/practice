/*
 * =====================================================================================
 *
 *       Filename:  ex8.cpp
 *
 *    Description:  tree outside school
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int main(void)
{
    int l,m,total = 0;
    int i;
    char *c;
    cin >> l >> m;
    c = (char*)malloc((l+1) * sizeof(char));
    if(c == NULL)
        return -1;
    memset(c, 0, (l+1)*sizeof(char));
    while(m-- > 0) 
    {
        int start, end;
        cin >> start >> end;
        for(int i = start; i <= end; i++)
            c[i] = 1;
    }
    
    for(i = 0; i <= l; i++)
        if(c[i] == 0)
            total += 1;
    cout << total << endl;
    free(c);
    return 0;
}
