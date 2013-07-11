/*
 * =====================================================================================
 *
 *       Filename:  cannonball.cpp
 *
 *    Description:  given the height of pyramid of cannonball, compute
 *    the number of connonballs it contains
 *
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int countCannonball(int height)
{
    if(height == 1)
        return 1;
    else
        return height * height + countCannonball(height - 1);
}

void print_count(int height)
{
    cout << "pyramid with height of " << height << " has "<<countCannonball(height) << " balls." << endl;
}
int main()
{
    print_count(1); //1
    print_count(2); //5
    print_count(3); //14
    return 0;
}
