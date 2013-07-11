/*
 * =====================================================================================
 *
 *       Filename:  histogram
 *
 *    Description:  draw histogram for given exam scores
 *
 *
 * =====================================================================================
 */
#include <iostream>
#include "vector.h"
#include "simpio.h"
#include "console.h"

void read_scores(string filename, Vector<int> & scores)
{
   ifstream infile;
   infile.open(filename.c_str());
   int cur_score;
   while(infile >>cur_score)
   {
       scores.add(cur_score);
   }
}

//cout scores in different range
void get_count(Vector<int> & scores, Vector<int> & count)
{
    for(int i = 0; i < scores.size(); i++)
    {
        int index = scores.get(i)/10;
        int cur_count = count.get(index);
        count.set(index, cur_count+1);
    }
}

void draw_histogram(Vector<int> & count)
{
    int size = count.size();
    for(int i = 0; i < size; i++)
    {
        if(i < 10)
            cout << i << "0s: ";
        else
            cout << i << "0: ";
        for(int j = 0; j < count.get(i); j++)
        {
            cout << "*";
        }
        cout << endl;
    }
}

int main(void)
{
    Vector<int> scores, count(11, 0);
    read_scores("score.txt", scores);
    get_count(scores, count);
    draw_histogram(count);

    return 0;
}

