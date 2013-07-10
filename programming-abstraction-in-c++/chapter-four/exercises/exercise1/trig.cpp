/*
 * =====================================================================================
 *
 *       Filename:  trig.cpp
 *
 *    Description:  produce a sin and cos table for numbers in [-90 90] with step 15
 *
 *        Version:  1.0
 *        Created:  2013年07月10日 16时49分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qiaoyuguo (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "console.h"
#include "gmath.h"

using namespace std;

void produceTable(void)
{
    cout << " theta | sin(theta) | cos(theta) |" <<endl;
    cout << "---------------------------------+" << endl;
    for(int i = -90; i <= 90; i += 15) 
    {
        cout <<" "<< setw(5) << i << " | " <<fixed << setw(10) << setprecision(7)<< sinDegrees(i)  << " | " << cosDegrees(i) << " |" << endl;
    }
}

int main(void)
{
    produceTable();

    return 0;
}
