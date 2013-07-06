/*
 * =====================================================================================
 *
 *       Filename:  GraphicsExample.cpp
 *
 *    Description:  GraphicsExample from <programming abstraction in c++>
 *
 *        Version:  1.0
 *        Created:  2013年07月06日 06时46分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qiaoyuguo (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "gwindow.h"
int main() {
  GWindow gw;
  cout << "This program draws a diamond, rectangle, and oval." << endl;
  double width = gw.getWidth();
  double height = gw.getHeight();
  gw.drawLine(0, height / 2, width / 2, 0);
  gw.drawLine(width / 2, 0, width, height / 2);
  gw.drawLine(width, height / 2, width / 2, height);
  gw.drawLine(width / 2, height, 0, height / 2);
  gw.setColor("BLUE");
  gw.fillRect(width / 4, height / 4, width / 2, height / 2);
  gw.setColor("GRAY");
  gw.fillOval(width / 4, height / 4, width / 2, height / 2);
  return 0;
}
