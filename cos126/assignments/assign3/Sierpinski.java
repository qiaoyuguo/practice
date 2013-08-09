public class Sierpinski
{
    public static void filledTriangle(double x, double y, double s)
    {
        double[] xl = new double[4];
        xl[0] = x - s/2; xl[1]= x + s/2;  xl[2]  = x; xl[3] = x-s/2;
        double[] yl = new double[4];
        yl[0] =Math.sqrt(3)/2*s+y; yl[1] = yl[0]; yl[2] = y; yl[3] = yl[0];
        StdDraw.filledPolygon(xl,yl);
    }
    public static void sierpinski(int n, double x, double y, double s)
    {
        if(n == 0)
        {
            return;
        }
        filledTriangle(x, y, s);
        sierpinski(n-1, x - s/2, y, s/2);
        sierpinski(n-1, x + s/2, y, s/2);
        sierpinski(n-1, x, y+Math.sqrt(3)/2*s, s/2);
    }

    public static void main(String[] args)
    {
        int n = Integer.parseInt(args[0]);

        StdDraw.line(0,0, 1,0);
        StdDraw.line(1,0, 0.5, Math.sqrt(3)/2);
        StdDraw.line(0.5, Math.sqrt(3)/2, 0, 0);
        sierpinski(n,  0.5, 0,0.5);;
    }
}
