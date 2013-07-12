/*
 * =====================================================================================
 *
 *       Filename:  CountSubsetWays.cpp
 *    Description:  Count the number of ways in which you can produce the target value  by choosing a subset of specified set.
 *
 * =====================================================================================
 */
#include <iostream>
#include "set.h"

using namespace std;

Set<int> createSet() ;
int countSubsetWays(Set<int> & set, int target);
void printResult(Set<int> & set, int target);

int main(void)
{
    Set<int> set = createSet();
    printResult(set, 5);

    set = createSet();
    printResult(set, 5);
}

Set<int> createSet() {
    Set<int> sampleSet;
    sampleSet += 1,3,4,5;
}

int countSubsetWays(Set<int> & set, int target)
{
    if(target == 0) 
        return 1;
    if(target < 0)
        return 0;
    int first = set.first();
    Set<int> rest = set - first;

    return countSubsetWays(set, target-first) + countSubsetWays(rest, target);
}

void printResult(Set<int> & set, int target)
{
   cout <<"the number of subset of set " << set.toString() << " whose elements sums to produces " << target << " is " << countSubsetWays(set, target) << endl;
}
