/*
 * =====================================================================================
 *
 *       Filename:  FractalTree.cpp
 *    Description:  draw Fractal Tree
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>
#include "gwindow.h"

using namespace std;

const double SIZE = 400;
const double THETA = 50; // angl of branch off trunk 

GPoint fractalTree(GWindow gw, GPoint pt, double size, double theta, int order);

int main()
{
    GWindow gw(600, 600);
    double cx = gw.getWidth()/2;
    double cy = gw.getHeight()/2;

    GPoint pt(cx,cy*2);
    //pt = gw.drawPolarLine(pt, SIZE, 90);

    fractalTree(gw, pt, 300, 0, 8);
    return 0;
}

GPoint fractalTree(GWindow gw, GPoint pt, double size, double theta, int order)
{
    pt = gw.drawPolarLine(pt, size, theta + 90);
    if(order == 0)
    {
        return pt;
    }
    fractalTree(gw, pt, size/2, theta - THETA, order - 1);
    return fractalTree(gw, pt, size/2, theta + THETA, order - 1);
}
