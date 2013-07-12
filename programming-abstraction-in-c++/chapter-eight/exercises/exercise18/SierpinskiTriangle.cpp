/*
 * =====================================================================================
 *
 *       Filename:  SierpinskiTriangle.cpp
 *    Description:  draw sierpinski triangle
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>
#include "gwindow.h"

using namespace std;

const double SIZE = 400;

// pt is the downleft point of triangle, size is the triangle size
void sierpinski(GWindow gw, GPoint pt, double size, int order);

int main(void)
{
    GWindow gw(600, 600);
    double cx = gw.getWidth()/2;
    double cy = gw.getHeight()/2; 
    GPoint pt(cx-SIZE/2, cy+SIZE*sqrt(3)/6);
    sierpinski(gw, pt, 300, 5);
}

void sierpinski(GWindow gw, GPoint pt, double size, int order)
{
    if(order == 0)
    {
        pt = gw.drawPolarLine(pt, size, 0);
        pt = gw.drawPolarLine(pt, size, 120 );
        pt = gw.drawPolarLine(pt, size, -120);
        return ;
    }
    sierpinski(gw,pt, size/2, order-1);
    sierpinski(gw, GPoint(pt.getX()+size/2, pt.getY()), size/2, order-1);
    sierpinski(gw, GPoint(pt.getX()+size/4, pt.getY()-size*sqrt(3)/4), size/2, order-1);
}
