/*
 * =====================================================================================
 *
 *       Filename:  check-board.cpp
 *
 *    Description:  draw checkerboard on the graphics window
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

#define BOARD_ROWS 8
#define BOARD_COLS 8
string revert_color(string color)
{
  if(color == "WHITE")
      return "GRAY";
  else
      return  "WHITE";
}
int main() {
  GWindow gw(600,600);
  //cout << "This program draws a diamond, rectangle, and oval." << endl;
  double width = gw.getWidth();
  double height = gw.getHeight();
  double piece_row_len = width/BOARD_ROWS;
  double piece_col_len = height/BOARD_COLS;
  string piece_color = "WHITE";
  double piece_y = 0.0;
  for(int i = 0; i < BOARD_ROWS; i++)
  {
      //double piece_x = piece_col_len/2;
      //double piece_y = piece_row_len/2;
      double piece_x = 0.0;
      for(int j = 0;  j < BOARD_COLS; j++)
      {
          gw.setColor(piece_color);
          gw.fillRect(piece_x, piece_y, piece_row_len, piece_col_len);
          gw.setColor("red");
          if((i+j) % 2 == 1)
          {
              double reduce_len = piece_row_len/10;
              gw.fillOval(piece_x+reduce_len/2, piece_y+reduce_len/2, piece_row_len-reduce_len,piece_col_len-reduce_len);
          }
          piece_x += piece_row_len;
          if(j < BOARD_COLS - 1)
              piece_color = revert_color(piece_color);
      }
      piece_y += piece_col_len;
  }
#if 0
  gw.drawLine(0, height / 2, width / 2, 0);
  gw.drawLine(width / 2, 0, width, height / 2);
  gw.drawLine(width, height / 2, width / 2, height);
  gw.drawLine(width / 2, height, 0, height / 2);
  gw.setColor("BLUE");
  gw.fillRect(width / 4, height / 4, width / 2, height / 2);
  gw.setColor("GRAY");
  gw.fillOval(width / 4, height / 4, width / 2, height / 2);
#endif
  return 0;
}
