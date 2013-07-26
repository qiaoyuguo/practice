/*
 * =====================================================================================
 *
 * Filename:  FillRegion.cpp
 * This program simulates the operation of paint-bucket tool by painting in black all
 * white pixels reacherable from the specified row and column without crossing existring
 * black pixel
 * =====================================================================================
 */

#include "grid.h"
#include "console.h"

const int ROW =  23;
const int COL = 19;

void init_pixels(Grid<bool> &pixels);
void display_pixels(Grid<bool> &pixels, int r, int c);

int main(int argc, char **argv)
{
    Grid<bool> pixels(ROW, COL);
    init_pixels(pixels);
    display_pixels(pixels, ROW, COL);

    return 0;
}

void init_pixels(Grid<bool> &pixels)
{
    int i;
    int row = pixels.numRows();
    int col = pixels.numCols();
    int half_col = col / 2;

    for(i = 0; i < half_col; i++)
    {
        pixels[i][half_col - i] = true;
        pixels[i][half_col + i] = true;
    }

    for(i = half_col; i < row; i++)
    {
        pixels[i][0] = true;
        pixels[i][col-1] = true;

        if(i - half_col  >= 0 && i - half_col <= 3)
        {
            pixels[i][3] = true;
            pixels[i][6] = true;
            pixels[i][12] = true;
            pixels[i][15] = true;
            if(i -half_col == 0 || i - half_col == 3)
            {
                pixels[i][4] = true;
                pixels[i][5] = true;
                pixels[i][13] = true;
                pixels[i][14] = true;
            }
        }

        if(row-1 -i <= 6 && row-1 -i >= 1)
        {
            pixels[i][7] = true;
            pixels[i][11] = true;
            if(row-1-i == 6)
                for(int j = 8; j <= 10; j++)
                    pixels[i][j] = true;
        }
        if(row -1 == i)
            for(int j = 0; j < col; j++)
                pixels[i][j] = true;
    }
}

void display_pixels(Grid<bool> &pixels, int r, int c)
{
   for(int i = 0; i < pixels.numRows(); i++) 
   {
       for(int j = 0; j < pixels.numCols(); j++)
       {
           cout << (pixels[i][j]?"T":" ") << " " ;
       }
       cout << endl;
   }
}
