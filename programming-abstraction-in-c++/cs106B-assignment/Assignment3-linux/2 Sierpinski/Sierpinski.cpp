/*
 * File: Sierpinski.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski Triangle problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <cmath>
#include <iostream>
#include "simpio.h"
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
    double edgeLen = getReal("Please input edge length[1,400]:");
    int order = getInteger("Please input order[1,10]:");
    sierpinski(gw, pt, edgeLen, order);

    return 0;
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
