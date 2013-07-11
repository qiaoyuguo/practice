/*
 * =====================================================================================
 *
 *       Filename:  CountHanoiMoves.cpp
 *    Description:  Count the number of moves to solve Towers of hanoi
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int CountMoves(int n)
{
    if(n == 1)
        return 1;
    return 2*CountMoves(n-1) + 1;
}

void print_result(int n)
{
    cout << "The moves of solving Tower of Hanoi of size " << n << " is " << CountMoves(n) << endl;
}

int main()
{
    print_result(1);
    print_result(5);

    return 0;
}
