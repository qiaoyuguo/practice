/*
 * =====================================================================================
 *
 *       Filename:  MagicSquare.cpp
 *
 *    Description:  check if a square is a magic square
 *
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>
#include "grid.h"

bool isMagicSquare(Grid<int> & grid)
{
    int i,j;
    int nRows = grid.numRows();
    int nCols = grid.numCols();
    if(nRows != nCols)
        return false;

    int digonal_sum = 0;
    for(i = 0; i < nRows; i++)
        digonal_sum += grid.get(i, i);

    int tmp_sum = 0;
    for(i = 0; i < nRows; i++)
        tmp_sum += grid.get(i, nRows - 1 - i);
    if(tmp_sum != digonal_sum)
        return false;

    for(i = 0; i < nRows; i++)
    {
        tmp_sum = 0;
        for(j = 0; j < nCols; j++)
        {
            tmp_sum += grid.get(i, j);
        }
        if(tmp_sum != digonal_sum)
            return false;
    }
    for(j = 0; j < nRows; j++)
    {
        tmp_sum = 0;
        for(i = 0; i < nCols; i++)
        {
            tmp_sum += grid.get(i, j);
        }
        if(tmp_sum != digonal_sum)
            return false;
    } 
    return true;
}

void print_grid(Grid<int> & grid)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout << grid.get(i,j) <<" ";
        }
        cout << endl;
    }
}
void init_grid(Grid<int> & grid)
{
    grid.resize(3,3);
    int a[3][3] = {{8,1,6},{3,5,7},{4,9,2}};
    //int a[3][3] = {{6,1,8},{3,5,7},{4,9,2}};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            grid.set(i,j , a[i][j]);
        }
}

int main(void)
{
    Grid<int> grid;
    init_grid(grid);
    print_grid(grid);
    if(isMagicSquare(grid))
        cout << "It's a magic square" << endl; 
    else
        cout << "It's not a magic square" << endl;
    return 0;
}
