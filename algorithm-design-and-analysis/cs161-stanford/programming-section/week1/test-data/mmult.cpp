/*
 * =====================================================================================
 *
 *       Filename:  mmult.c
 *
 *    Description:  matrix multiply
 *          Usage:  mmult < <input file> > <output file>
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;

#define MAX  1000

int mater[MAX][MAX]; // matrix to multiply
int matee[MAX][MAX]; // matrix to be multiplied
int result[MAX][MAX];

int main(int argc, char **argv)
{
    int m, n, p; //first matrix row and column number and second matrix column number
    int i,j,k;

    cin >> m >> n >> p;
    
    for(i= 0; i < m; i++)
        for(j = 0; j < n; j++)
            cin >> mater[i][j];
    
    for(i = 0; i < n; i++)
        for(j = 0; j < p; j++)
            cin >> matee[i][j];
   
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < p; j++)
        {
            for(k = 0; k < n; k++)
                result[i][j] += mater[i][k] * matee[k][j];
            cout <<result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

