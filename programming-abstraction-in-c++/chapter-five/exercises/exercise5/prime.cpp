/*
 * =====================================================================================
 *
 *       Filename:  prime.cpp
 *
 *    Description:  generate list of primes between 2 and 1000
 *    using sieve of EratoThenes which gradually remove multiple of prime numbers
 *
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>
#include "vector.h"

void print_integers(Vector<int> & integers)
{
    int size = integers.size();
    for(int i = 0; i < size; i++)
        cout << integers.get(i) << " ";
    cout << endl;
}
void init_integers(Vector<int> &integers, int n)
{
    for(int i = 2; i <= n; i++)
    {
        integers.add(i);
    }
}

void delete_non_prime(Vector<int> & integers)
{
    int size = integers.size();
    Vector<int> flag(size, 0); // can be -1 or 1 or 0, zero mean initial status, -1 mean crossed out, 1 means circled
                            
    for(int i = 0; i < size; i++)
    {
        int j;
        for(j = i; j < size; j++)
            if(flag.get(j) == 0)
                break;
        if(j >= size)
            break;

        flag.set(j, 1);
        int circle_int= integers.get(j);
        for(;j < size; j++)
            if(flag.get(j) == 0)
            {
                if(integers.get(j) % circle_int == 0)
                    flag.set(j, -1);
            }
    }
    for(int i = size-1; i >= 0; i--)
        if(flag.get(i)==-1)
            integers.remove(i);
}

int main(void)
{
    Vector<int> integers;
    init_integers(integers, 1000);
    //print_integers(integers);
    delete_non_prime(integers);
    print_integers(integers);
}
