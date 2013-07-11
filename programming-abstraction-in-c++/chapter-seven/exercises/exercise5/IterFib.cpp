/*
 * =====================================================================================
 *
 *       Filename:  IterFib.cpp 
 *    Description:  compute fibnacci value using iterative method
 *
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

/* Fibnacci value: 1 1 2 3 ... */
int iterFib(int k)
{
    int a = 1;
    int b = 1;
    for(int i = 1; i < k; i++)
    {
        int tmp  = a+b;
        a = b;
        b = tmp;
    }
    return a;
}

void print_fib(int k)
{
    cout << "the " << k << " number in fibnacci is: " << iterFib(k) << endl;
}

int main()
{
    for(int i = 1; i <= 5; i++)
        print_fib(i);
    return 0;
}
