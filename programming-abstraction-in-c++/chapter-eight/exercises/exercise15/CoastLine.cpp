/*
 * =====================================================================================
 *
 *       Filename:  CountHanoiMoves.cpp
 *    Description:  Count the number of moves to solve Towers of hanoi
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>
#include "random.h"
#include "gwindow.h"

using namespace std;

const double WIDTH = 600;
const double HEIGHT = 800;
const int ORDER = 5;
const double SIZE = WIDTH*2/3;

GPoint drawCoastLine(GWindow gw, GPoint pt, double size,double theta, double order);


int main(void)
{
    GWindow gw(WIDTH, HEIGHT);
    int width = gw.getWidth();
    int height = gw.getHeight();

    GPoint pt(width/2 - SIZE/2, height/2 - sqrt(3)*SIZE/6 );
    pt = drawCoastLine(gw,pt, SIZE, 0, ORDER);
    pt = drawCoastLine(gw,pt, SIZE, -120, ORDER);
    pt = drawCoastLine(gw,pt, SIZE, 120, ORDER);

    return 0;
}
bool randomBool()
{
    int n = randomInteger(0,1);
    if(n == 1)
        return true;
    else
        return false;
}

GPoint drawCoastLine(GWindow gw, GPoint pt, double size,double theta, double order)
{
    if(order == 0)
        return gw.drawPolarLine(pt, size, theta);

    pt = drawCoastLine(gw, pt, size/3, theta, order - 1);
    bool b = randomBool();
    if(b)
    {
        pt = drawCoastLine(gw, pt, size/3, theta+60, order - 1);
        pt = drawCoastLine(gw, pt, size/3, theta-60, order - 1);
    }
    else
    {
        pt = drawCoastLine(gw, pt, size/3, theta-60, order - 1);
        pt = drawCoastLine(gw, pt, size/3, theta+60, order - 1);
    }

    return drawCoastLine(gw, pt, size/3, theta, order-1);
}
