/*
 * =====================================================================================
 *
 *       Filename:  ex2.cpp
 *
 *    Description:  judge the scores
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int main(void)
{
    int score;
    cin >> score;

    if(score >= 95 && score <= 100)
        cout << 1 << endl;
    else if(score >= 90 && score < 95)
        cout << 2 << endl;
    else if(score >= 85 && score < 90)
        cout << 3 << endl;
    else if(score >= 80 && score < 85)
        cout << 4 << endl;
    else if(score >= 70 && score < 80)
        cout << 5 << endl;
    else if(score >= 60 && score < 70)
        cout << 6 << endl;
    else
        cout << 7 << endl;

    return 0;
}
