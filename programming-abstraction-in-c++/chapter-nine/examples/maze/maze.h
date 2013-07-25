/*
 * File: maze.h
 * --------------
 *  This interface exports the Maze class
 */

#ifndef _maze_h
#define _maze_h

#include <string>
#include "grid.h"
#include "gwindow.h"
#include "point.h"

/*
 * Class: Maze
 * ----------------
 *  This class represents a two-dimensional maze contained in a rectangular
 *  grid of squares. The maze is read in from a data file in which the 
 *  characters '+', '-', and '|' represent corners, horizontal walls, and 
 *  vertical walls, repectively; spaces represent open passageway squares.
 *  The starting postion is indicated by the character 'S'. For example,
 *  The following data file defines a simple maze:
 *
 *  +-+-+-+-+-+
 *  |         |
 *  + +-+ + +-+
 *  |S  |     |
 *  +-+-+-+-+-+
 */

class Maze{
    public:
        /* 
         * Constructor: Maze
         * Usage: Maze maze(filename);
         *        Maze maze(filename, gw);
         * ------------------------------------
         *  constructs a new maze by readint he specified data file. If the
         *  second argument is supplied, the maze is displayed in the center
         *  of the graphics window.
         *  */
        Maze(std::string filename);
        Maze(std::string filename, GWindow gw);

        /* 
         * Method: getStartPosition
         * Usage: Point start = maze.getStartPostion();
         * ----------------------------------------------
         * Return a Point indicating the coordinate of the starting point
         * */
        Point getStartPosition();

        /*
         * Method: isOutSide
         * Usage: if (maze.isOutSide()) ....
         * -----------------------------------
         * Returns true if the specified point is outside the boundary of 
         * the maze.
         */
        bool isOutside(Point pt);

        /*
         * Method: wallExists
         * usage: if (maze.wallExists(pt, dir)) . . .
         * Returns true if there is a wall in direction dir from the squares
         * at pt.
         * */
        bool wallExists(Point pt, Direction dir);

        /*
         * method: markSquare
         * Usage: maze.markSquare(pt);
         * -----------------------------
         *  Marks the specified square in the maze.
         */
         void markSquare(Point pt);

         /*
          * Method: unmarkSquare
          * Usage: maze.unmarkSquare(pt);
          * ------------------------------
          *  Unmarks the specified square in the maze.
          */
         void unmarkSquare(Point pt);

         /* 
          * Method: isMarked
          * Usage: if (maze.isMarked(pt) . . .
          * ----------------------------------
          *  Returns true if the specified square is marked
          * */
          bool isMarked(Point pt);
};

#endif
