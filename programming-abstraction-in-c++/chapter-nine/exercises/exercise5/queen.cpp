/*
 * =====================================================================================
 *
 * Filename:  queen.cpp
 * This program deals with the N-queen problem, display a solution if exists or report
 * that no  solution exists.
 * =====================================================================================
 */

#include "simpio.h"
#include "gwindow.h"
#include "grid.h"
//#include "console.h"

#define WIDTH  600
#define HEIGHT  WIDTH

typedef enum Direction{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
} Direction;


void draw_ChessBoard(Grid<bool> &ChessBoard, GWindow &gw);
GPoint adjacentGPoint(GPoint start, Direction dir) ;
bool solve(Grid<bool> &ChessBoard, GPoint start,  int queen_to_find);
bool solveChessBoard(Grid<bool> &ChessBoard);
bool can_be_placed(Grid<bool> &ChessBoard, GPoint start);
void display_ChessBoard(Grid<bool> &ChessBoard);

int main(int argc, char **argv)
{
    GWindow gw(WIDTH, HEIGHT);
    int n;
#if 1
    do{
        n = getInteger("Please input the board size(int between 1 and 20):");
        if(n <= 0 ||  n >= 20)
            cout << "you input a wrong size, please input a correct size." << endl;
        else
            break;
    }while(n <= 0 || n >= 20);
#endif
    Grid<bool> ChessBoard(n, n);

#if 0
    can_be_placed(ChessBoard, GPoint(5,3));
    display_ChessBoard(ChessBoard);
#endif 
#if 1
    if(solveChessBoard(ChessBoard))
    {
        draw_ChessBoard(ChessBoard, gw);
    }
    else
        cout << "can't find a solution for " << ChessBoard.numRows() << "x" << ChessBoard.numRows() << " board" <<endl;
#endif
    return 0;
}

bool solveChessBoard(Grid<bool> &ChessBoard)
{
    GPoint start(2,3);
    return solve(ChessBoard, start, ChessBoard.numRows());
}

bool can_be_placed(Grid<bool> &ChessBoard, GPoint start)
{
    int i;
    int board_size = ChessBoard.numRows();
    int start_x = start.getX();
    int start_y = start.getY();
#if 1
    if(start_x < 0 || start_x >= board_size || start_y < 0 || start_y >= board_size)
        return false;
#endif
    for(i = 0; i < board_size; i++)
    {
        if(i != start_x)
        {
            //ChessBoard[i][start_y] = true;
#if 1
            if(ChessBoard[i][start_y])
                return false;
#endif
        }
        if(i != start_y)
        {
            //ChessBoard[start_x][i] = true;
#if 1
            if(ChessBoard[start_x][i] == true)
                return false;
#endif
        }
    }
    if(start_x >= start_y)
    {
        for(i = 0; i < board_size - (start_x- start_y); i++)
            if(i != start_y)
            {
                //cout << start_x-start_y+i << "," << i << endl;
                //ChessBoard[start_x-start_y+i][i] = true;
#if 1
                if(ChessBoard[start_x-start_y+i][i])
                    return false;
#endif
            }
    }
    else 
    {
        for(i = 0; i < board_size - (start_y- start_x); i++)
            if(i != start_x)
            {
                //ChessBoard[i][start_x-start_y+i] = true;
                //cout << i  << "," << start_x-start_y+i << endl;
#if 1
                if(ChessBoard[i][start_x-start_y+i])
                    return false;
#endif
            }
    }

    if(start_x + start_y <= board_size - 1)
    {
        for(i = 0; i <= start_x + start_y; i++)
            if(i != start_x)
            {
                //ChessBoard[i][start_x + start_y - i] = true;
                //cout << i << "," << start_x + start_y -i << endl;
#if 1
                if(ChessBoard[i][start_x + start_y - i])
                    return false;
#endif
            }
    }
    else
    {
        for(i = start_x + start_y - (board_size - 1); i < board_size; i++)
            if(i != start_y)
            {
                //cout << start_x + start_y -i  << " " << i <<  endl;
                //ChessBoard[start_x + start_y - i][i] = true;
#if 1
                if(ChessBoard[start_x + start_y - i][i])
                    return false;
#endif
            }

    }

    return true;
}
// This is the core function to solve queen problem
// queen_to_find is the number of queens to be find.
bool solve(Grid<bool> &ChessBoard, GPoint start,  int queen_to_find)
{
    if(queen_to_find == 0)
        return true;

    int i,j;
    int board_size = ChessBoard.numRows();
    int start_x = start.getX();
    int start_y = start.getY();

    ChessBoard.set(start_x, start_y, true);
    display_ChessBoard(ChessBoard);
    Direction dirs[4] = {NORTH, EAST,SOUTH, WEST};
    for(int i = 0; i < 4; i++)
    {
        GPoint  adjPoint = adjacentGPoint(start, dirs[i]);
        if(!can_be_placed(ChessBoard, adjPoint))
            continue;
        if(solve(ChessBoard, adjPoint, queen_to_find - 1 ))
            return true;
    }
    ChessBoard.set(start_x, start_y, false);
    return false;
}
/*
 * Display ChessBoard in console window
 */
void display_ChessBoard(Grid<bool> &ChessBoard)
{
   for(int i = 0; i < ChessBoard.numRows(); i++) 
   {
       for(int j = 0; j < ChessBoard.numCols(); j++)
       {
           cout << (ChessBoard[i][j]?"T":" ") << " " ;
       }
       cout << endl;
   }
   cout << endl;
}

/*
 * Display ChessBoard in graphics window
 */
void draw_ChessBoard(Grid<bool> &ChessBoard, GWindow &gw)
{
    int row = ChessBoard.numRows();
    int col = ChessBoard.numCols();
    double width = gw.getWidth();
    double height = gw.getHeight();
    double cell_width = width/col;
    double cell_height = height/row;

    for(int i = 0; i < row; i++)
    {
        gw.drawLine(0, i*cell_height, width, i*cell_height);
        gw.drawLine(i*cell_width, 0, i*cell_width, height);
    }

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
