/*
 * =====================================================================================
 *
 *       Filename:  ex1.cpp
 *
 *    Description:  count characters 
 *
 * =====================================================================================
 */
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int main(void)
{
    int i, len;
    int c[5] = {0}; /* correspond to 'a', 'e', 'i', 'o', 'u' */
    char buf[100] = {0};
    gets(buf);
    len = strlen(buf);
    for(i = 0; i < len; i++)
        if(buf[i] == 'a')
            ++c[0];
        else if(buf[i] == 'e')
            ++c[1];
        else if(buf[i] == 'i')
            ++c[2];
        else if(buf[i] == 'o')
            ++c[3];
        else if(buf[i] == 'u')
            ++c[4];
    for(i = 0; i < 4; i++)
        printf("%d ", c[i]);
    printf("%d\n", c[4]);

    return 0;
}
