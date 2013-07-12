/*
 * =====================================================================================
 *
 *       Filename:  HFractal.cpp
 *    Description:  draw H-Fractal in which repeated pattern is shaped like 
 *    an elongated letter 'H'
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>
#include "random.h"
#include "gwindow.h"

using namespace std;

void drawHFractal(GWindow gw, double x, double y, double size, int order);

//void drawHFractal(GWindow gw, double & x, double & y, double   size, int  order);
int main(void)
{
    GWindow gw(600,600);
    double xc = gw.getWidth()/2;
    double yc = gw.getHeight()/2;
    drawHFractal(gw, xc, yc, 100, 3);

    return 0;
}

void drawHFractal(GWindow gw, double x, double y, double size, int order)
//void drawHFractal(GWindow gw, double & x, double & y, double   size, int  order)
{
    int upleft_x = x - size/2;
    int upleft_y = y - size/2;
    int downright_x = x + size/2;
    int downright_y = y + size/2;
    gw.drawLine(upleft_x, upleft_y, upleft_x, downright_y );
    gw.drawLine(upleft_x, y, downright_x, y);
    gw.drawLine(downright_x, upleft_y, downright_x, downright_y);
    if(order == 0)
    {
        return;
    }
    drawHFractal(gw, upleft_x, upleft_y, size/2, order-1);
    drawHFractal(gw, upleft_x, downright_y, size/2, order-1);
    drawHFractal(gw, downright_x, upleft_y, size/2, order-1);
    drawHFractal(gw, downright_x, downright_y, size/2, order-1);
}
