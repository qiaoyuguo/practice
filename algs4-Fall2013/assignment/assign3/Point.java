/*************************************************************************
 * Name:
 * Email:
 *
 * Compilation:  javac Point.java
 * Execution:
 * Dependencies: StdDraw.java
 *
 * Description: An immutable data type for points in the plane.
 *
 *************************************************************************/

import java.util.Comparator;

public class Point implements Comparable<Point> {

    // compare points by slope
    public final Comparator<Point> SLOPE_ORDER = new SlopeOrder(this);       // YOUR DEFINITION HERE

    private final int x;                              // x coordinate
    private final int y;                              // y coordinate

    // create the point (x, y)
    public Point(int x, int y) {
        /* DO NOT MODIFY */
        this.x = x;
        this.y = y;
    }

    // plot this point to standard drawing
    public void draw() {
        /* DO NOT MODIFY */
        StdDraw.point(x, y);
    }

    // draw line between this point and that point to standard drawing
    public void drawTo(Point that) {
        /* DO NOT MODIFY */
        StdDraw.line(this.x, this.y, that.x, that.y);
    }

    // slope between this point and that point
    public double slopeTo(Point that) {
        /* YOUR CODE HERE */
        if(this.x == that.x)
            return Double.POSITIVE_INFINITY;
        if(this.y == that.y)
            return +0.0;
        return (this.y - that.y)/(this.x - that.x);
    }

    // is this point lexicographically smaller than that one?
    // comparing y-coordinates and breaking ties by x-coordinates
    public int compareTo(Point that) {
        /* YOUR CODE HERE */
        if(this.y < that.y)
            return -1;
        else if(this.y == that.y && this.x < that.x)
            return -1;
        return +1;
    }

    // return string representation of this point
    public String toString() {
        /* DO NOT MODIFY */
        return "(" + x + ", " + y + ")";
    }

    private static class SlopeOrder implements Comparator<Point> 
    {
        private Point startPoint; 

        public SlopeOrder(Point p)
        {
            startPoint = p;
        }
        public int compare(Point p, Point q)
        {
            double pSlope = startPoint.slopeTo(p);
            double qSlope = startPoint.slopeTo(q);
            if(pSlope == Double.POSITIVE_INFINITY && qSlope == Double.POSITIVE_INFINITY)
                return 0;
            else if(pSlope == Double.POSITIVE_INFINITY)
            {
                if(qSlope > 0)
                    return +1;
                else 
                    return -1;
            }
            else if(qSlope == Double.POSITIVE_INFINITY)
            {
                if(pSlope > 0)
                    return +1;
                else 
                    return -1;
            }
            else if(pSlope > qSlope)
                return +1;
            else if(pSlope < qSlope)
                return -1;
            else 
                return 0;
        }
    }

    // unit test
    public static void main(String[] args) {
        /* YOUR CODE HERE */
        Point p = new Point(3,4);
        Point q = new Point(4,8);
        StdOut.printf("%.3f %d\n", p.slopeTo(q), p.compareTo(q));
    }
}
