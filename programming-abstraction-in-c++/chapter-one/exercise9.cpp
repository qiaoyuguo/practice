/*
 * =====================================================================================
 *
 *       Filename:  exercise9.cpp
 *
 *    Description:  display prime factorization of number n
 *
 *        Version:  1.0
 *        Created:  2013年07月05日 21时37分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qiaoyuguo (), 
 *   Organization:  
 *
 * =====================================================================================
 */
//#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

bool is_prime(int n)
{
    if(n == 2 || n == 3)
        return true;
    int tmp = std::sqrt(n);
    for(int i = 2; i <= tmp; i++)
        if(n %i == 0)
            return false;
    return true;
}
void get_prime_factor(int n)
{
    int i = 2;
    while(n != 1)
    {
        if(is_prime(i) && n % i == 0)
        {
            n /= i;
            cout << i ;
            if(n != 1)
                cout <<"*";
        }
        ++i;
    } 
    cout <<endl;
}
int main(void)
{
    cout <<"This program factors a number." <<endl;
    cout <<"Enter number to be factored: ";
    int input_num;
    cin >>input_num;
    get_prime_factor(input_num);

    return 0;
}
