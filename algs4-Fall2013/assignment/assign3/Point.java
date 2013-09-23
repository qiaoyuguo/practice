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
        if(this == null || that == null)
            throw new NullPointerException();
        if(this.x == that.x)
        {
            if(this.y == that.y)
                return Double.NEGATIVE_INFINITY;
            else
                return Double.POSITIVE_INFINITY;
        }
        if(this.y == that.y)
            return +0.0;
        return (double)(this.y - that.y)/(this.x - that.x);
    }

    // is this point lexicographically smaller than that one?
    // comparing y-coordinates and breaking ties by x-coordinates
    public int compareTo(Point that) {
        /* YOUR CODE HERE */
        if(this == null || that == null)
            throw new NullPointerException();
        if(this.y < that.y)
            return -1;
        else if(this.y == that.y && this.x < that.x)
            return -1;
        else if(this.y == that.y && this.x == that.x)
            return 0;
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

            if(p == null || q == null)
                throw new NullPointerException();
            double pSlope = startPoint.slopeTo(p);
            double qSlope = startPoint.slopeTo(q);
            //if((pSlope == Double.POSITIVE_INFINITY || pSlope == Double.NEGATIVE_INFINITY) && (qSlope == Double.POSITIVE_INFINITY ||qSlope == Double.NEGATIVE_INFINITY ))
            //    return 0;
            //else if(pSlope == Double.POSITIVE_INFINITY || qSlope == Double.NEGATIVE_INFINITY )
            /*
            if(pSlope == Double.POSITIVE_INFINITY || qSlope == Double.NEGATIVE_INFINITY )
            {
                //if(qSlope > 0)
                //    return -1;
                //else 
                //    return +1;
                return +1;
            }
            else if(qSlope == Double.POSITIVE_INFINITY || pSlope ==  Double.NEGATIVE_INFINITY )
            {
                return -1;
            }
            else*/
            if(pSlope > qSlope)
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
        Point r = new Point(3, 9);
        Point s = new Point(9, 4);
        Point t = new Point(5, 1);
        Point u = new Point(5,1);
        Point p1 = new Point(2,8);
        Point p2 = new Point(2,8);
        Point p3 = new Point(2,5);
        
        StdOut.printf("%.3f %d\n", p.slopeTo(q), p.compareTo(q));
        StdOut.printf("%.3f %d\n", p.slopeTo(r), p.compareTo(r));
        StdOut.printf("%.3f %d\n", p.slopeTo(s), p.compareTo(s));
        StdOut.printf("%.3f %d\n",q.slopeTo(s), q.compareTo(s));
        StdOut.printf("%.3f %d\n",s.slopeTo(r), s.compareTo(r));
        StdOut.printf("%.3f %d\n",t.slopeTo(u), t.compareTo(u));
        StdOut.printf("%d\n", p1.SLOPE_ORDER.compare(p2,p3));
    }
}
