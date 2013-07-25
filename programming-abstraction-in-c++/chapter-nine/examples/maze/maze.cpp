/*
 * =====================================================================================
 *
 *       Filename:  maze.cpp
 *
 *    Description:  maze implementation
 *
 * =====================================================================================
 */
#include "maze.h"
/*
 * Function: solveMaze
 * Usage: solveMaze(maze, start)
 * ---------------------------------
 *  Attempts to generate a solution to the current maze from the specified
 *  start point. The solveMaze function return true if the maze has a 
 *  solution and false otherwise. The implementation uses recusion to solve 
 *  the submazes that result from marking the current square and moving one
 *  step along each open passenage.
 * */

bool solveMaze(Maze &maze, Point start) {
    if (maze.isOutside(start)) return true;
    if (maze.isMarked(start)) return false;
    maze.markSquare(start);
    for(Direction dir = NORTH; dir <= WEST; dir++) {
        if(!maze.wallExists(start, dir)){
            if (solveMaze(maze, adjacentPoint(start, dir))) {
                return true;
            }
        }
    }

    maze.unmarkSquare(start);
    return false;
}

/*
 * Function: adjcentPoint
 * Usage: Point finish = adjacentPoint(start, dir)
 * ------------------------------------------------
 *  Returns the point that results from moving one square from start in the
 *  direction specified by dir. For example, if pt is the point(1,1), 
 *  calling adjcentPoint(pt, EAST) returns the  point(2,1). To maintain the
 *  consistency with the graphic package, the y coordinate increase as you
 *  move downward on the screen. Thus, moving NORTH decreases the y 
 *  component, and moving SOUTH increase it.
 */
Point adjacentPoint(Point start, Direction dir) {
    switch (dir) {
        case NORTH: return Point(start.getX(), start.getY() - 1);
        case EAST:  return Point(start.getX() + 1, start.getY());
        case SOUTH: return Point(start.getX(), start.getY() + 1);
        case WEST: return Point(start.getX() - 1, start.getY());
    }
    return start;
}
