/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the coin-flipping problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
using namespace std;

int main() {
   // [TODO: fill in the code]
   int consecutive_heads_num = 0;
   int total_num = 0;
   while(consecutive_heads_num < 3)
   {
       int rand_num = randomInteger(0,1);
       ++total_num;
       if(rand_num == 0)
       {
           cout << "heads" <<endl;
           ++consecutive_heads_num;
       }
       else
       {
           cout << "tails" <<endl;
           consecutive_heads_num = 0;
       }
   }
   cout << "It took " <<total_num <<" flips to get " << consecutive_heads_num << " consecutive heads." << endl;

   return 0;
}
