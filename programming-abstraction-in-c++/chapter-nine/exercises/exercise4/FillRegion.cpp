/*
 * =====================================================================================
 *
 * Filename:  FillRegion.cpp
 * This program simulates the operation of paint-bucket tool by painting in black all
 * white pixels reacherable from the specified row and column without crossing existring
 * black pixel
 * =====================================================================================
 */

#include "gwindow.h"
#include "grid.h"
#include "console.h"

#define WIDTH  400
#define HEIGHT  300

const int ROW =  23;
const int COL = 19;

void init_pixels(Grid<bool> &pixels);
void display_pixels(Grid<bool> &pixels);
void draw_pixels(Grid<bool> &pixels, GWindow &gw);

int main(int argc, char **argv)
{
    GWindow gw(WIDTH, HEIGHT);
    Grid<bool> pixels(ROW, COL);
    init_pixels(pixels);
    //display_pixels(pixels);
    draw_pixels(pixels, gw);

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

/*
 * Display pixels in console window
 */
void display_pixels(Grid<bool> &pixels)
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

/*
 * Display pixels in graphics window
 */
void draw_pixels(Grid<bool> &pixels, GWindow &gw)
{
    int row = pixels.numRows();
    int col = pixels.numCols();
    double rect_width = gw.getWidth() / row; 
    double rect_height = gw.getHeight() / col;

    double oval_width = rect_width - 2;
    double oval_height = rect_height - 2;

    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
        {
            if(pixels[i][j])
                gw.setColor("black");
            else
                gw.setColor("gray");
            gw.fillOval(i*rect_width,j*rect_height, oval_width, oval_height);
        }
}
