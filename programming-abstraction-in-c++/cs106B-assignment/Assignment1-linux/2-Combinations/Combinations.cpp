/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the recursive combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

#define MAX_LINE 10

int combine(int n, int k)
{
    if(k == 0 || k == n)
        return 1;
    return combine(n-1,k-1) + combine(n-1, k);
}
int main() {
   for(int n = 0; n < MAX_LINE; n++)
   {
       for(int i = 0; i <= n; i++)
           cout << combine(n, i) <<" ";
       cout << endl;
    }
   return 0;
}
