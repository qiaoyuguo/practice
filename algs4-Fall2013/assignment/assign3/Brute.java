import java.util.Collections;
import java.util.ArrayList;

public class Brute
{
    private static boolean sameLine(Point p1, Point p2, Point p3, Point p4)
    {
        if(bitwiseEqual(p1.slopeTo(p2), p1.slopeTo(p3)) && bitwiseEqual(p1.slopeTo(p2), p1.slopeTo(p4)) && bitwiseEqual(p1.slopeTo(p3), p3.slopeTo(p4)) )
            return true;
        else
            return false;
    }
    private static boolean bitwiseEqual(double x, double y)
    {
        return Double.doubleToLongBits(x) == Double.doubleToLongBits(y);
    }
    public static void main(String[] args)
    {
        In infile = new In(args[0]);
        int N = infile.readInt(); 
        ArrayList<Point> pts = new ArrayList<Point>();
        for(int i = 0; i < N; i++)
        {
            int x = infile.readInt();
            int y = infile.readInt();
            pts.add(new Point(x,y));
        }
        Collections.sort(pts);

        for(int i = 0; i < N; i++)
            for(int j = i+1; j < N; j++)
                for(int k = j+1; k < N; k++)
                    for(int l = k+1; l < N; l++)
                        if(i < j && j < k && k < l)
                        {
                            //StdOut.println(pts[i]+" " + pts[j] + " " + pts[k] + " " + pts[l]);
                            //StdOut.println(pts[i].slopeTo(pts[j]) +" "+ pts[j].slopeTo(pts[k]) + " " +  pts[k].slopeTo(pts[l]));
                            if(sameLine(pts.get(i), pts.get(j), pts.get(k), pts.get(l)))
                            {
                                StdOut.println(pts.get(i)+ " -> " + pts.get(j)+ " -> " + pts.get(k) + " -> " + pts.get(l));
                            }
                        }

    }
}
