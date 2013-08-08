public class PlotFilter
{
    public static void main(String[] args)
    {
        double xmin = StdIn.readDouble();
        double ymin = StdIn.readDouble();
        double xmax = StdIn.readDouble();
        double ymax = StdIn.readDouble();

        StdDraw.setXscale(xmin, ymin);
        StdDraw.setYscale(xmax, ymax);

        while(!StdIn.isEmpty())
        {
            double x = StdIn.readDouble();
            double y = StdIn.readDouble();

            StdDraw.point(x,y);
        }
    }
}
