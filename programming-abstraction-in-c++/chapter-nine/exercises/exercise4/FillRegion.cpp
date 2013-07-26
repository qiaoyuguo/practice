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

#define WIDTH  300
#define HEIGHT  400

typedef enum Direction{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
} Direction;

const int ROW =  23;
const int COL = 19;
Grid<bool> pixels(ROW, COL);

void init_pixels(Grid<bool> &pixels);
void display_pixels(Grid<bool> &pixels);
void draw_pixels(Grid<bool> &pixels, GWindow &gw);
bool FillRegion(Grid<bool> &pixels, GPoint start);
GPoint adjacentGPoint(GPoint start, Direction dir) ;
void fill_and_display(Grid<bool> &pixels);

int main(int argc, char **argv)
{
    GWindow gw(WIDTH, HEIGHT);
    init_pixels(pixels);
    fill_and_display(pixels);
    display_pixels(pixels);
    draw_pixels(pixels, gw);

    return 0;
}

void fill_and_display(Grid<bool> &pixels)
{
    //Grid<bool> marked(pixels.numRows(), pixels.numCols());
    GPoint start(3,3); // upleft corner
    //GPoint start(2,12); //upright corner
    //GPoint start(10,10);// middle
    FillRegion(pixels, start);
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
    double rect_width = gw.getWidth() / col; 
    double rect_height = gw.getHeight() / row;

    double oval_width = rect_width - 2;
    double oval_height = rect_height - 2;

    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
        {
            if(pixels[i][j])
                gw.setColor("black");
            else
                gw.setColor("gray");
            gw.fillOval(j*rect_width,i*rect_height, oval_width, oval_height);
        }
}

//start is the start point to fill region
bool FillRegion(Grid<bool> &pixels, GPoint start)
{
    int cur_row = start.getX();
    int cur_col = start.getY();
    if(pixels.get(cur_row, cur_col)) return false;

    pixels.set(cur_row, cur_col, true);
    int row = pixels.numRows();
    int col = pixels.numCols();
    Direction dirt[4] = {NORTH, EAST, SOUTH, WEST};
    for(int i = 0; i < 4; i++)
    {
        GPoint adjPoint = adjacentGPoint(start, dirt[i]);
        int adj_row = adjPoint.getX();
        int adj_col = adjPoint.getY();
        if(adj_row < 0 || adj_row >= row || adj_col < 0 || adj_col >= col)
            return false;
        cout << adj_row  << " "<< adj_col << endl;
        if(!pixels.get(adj_row, adj_col) && FillRegion(pixels, adjPoint)) 
        {
            return true;
        }
    }
    return false;
}

GPoint adjacentGPoint(GPoint start, Direction dir) {
    switch (dir) {
        case NORTH: return GPoint(start.getX(), start.getY() - 1);
        case EAST:  return GPoint(start.getX() + 1, start.getY());
        case SOUTH: return GPoint(start.getX(), start.getY() + 1);
        case WEST: return GPoint(start.getX() - 1, start.getY());
    }
    return start;
}
