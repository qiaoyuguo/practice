/*
 * =====================================================================================
 *
 *       Filename:  ex3.cpp
 *
 *    Description:  simple arithmetic expression
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int main(void)
{
    int a, b;
    char c;
    int result;

    cin >> a;
    while(cin >> c)
    {
        if(c != ' ')
            break;
    }
    cin >> b;
    if(c == '+')
        result = a + b;
    else if(c == '-')
        result = a -b;
    else if(c == '*')
        result = a * b;
    else if(c == '/')
        result = a /b;
    else if(c == '%')
        result = a % b;

    cout << result << endl;

    return 0;
}
