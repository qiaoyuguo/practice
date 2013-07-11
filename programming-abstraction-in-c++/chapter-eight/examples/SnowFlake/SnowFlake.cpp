/*
 * =====================================================================================
 *
 *       Filename:  SnowFlake.cpp 
 *    Description:  Draws a Koch fractal snowflake.
 *
 * =====================================================================================
 */
#include <iostream>
#include <cmath>
#include "gwindow.h"

using namespace std;

/* Constants */
const double SIZE = 200;
const int ORDER = 4;
/* Function prototye */
GPoint drawFractalLine(GWindow & gw, GPoint pt,
                       double r, double theta, int order);

/* Main program  */
int main() {
    GWindow gw; 
    cout << "Program to draw a snowflake fractal." << endl;
    double cx = gw.getWidth() / 2;
    double cy = gw.getHeight() / 2;
    GPoint pt(cx - SIZE/2, cy - sqrt(3.0) * SIZE / 6);
    pt = drawFractalLine(gw, pt, SIZE, 0, ORDER);
    pt = drawFractalLine(gw, pt, SIZE, -120, ORDER);
    pt = drawFractalLine(gw, pt, SIZE, +120, ORDER);
    return 0;
}

GPoint drawFractalLine(GWindow & gw, GPoint pt,
                       double r, double theta, int order) {
    if (order == 0) {
        return gw.drawPolarLine(pt, r, theta);
    } else  {
        pt = drawFractalLine(gw, pt, r / 3, theta, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta + 60, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta - 60, order - 1);
        return drawFractalLine(gw, pt, r/3, theta, order - 1);
    }
}
