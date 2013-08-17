public class Charge
{
    private final double rx, ry;
    private final double q;

    public Charge(double x0, double y0, double q0)
    {
        rx = x0;
        ry = y0;
        q = q0;
    }

    double potentialAt(double x, double y)
    {
        double k = 8.99e09;
        double dx = x - rx;
        double dy = y - ry;
        return k * q / Math.sqrt(dx * dx + dy * dy);
    }

    public String toString()
    {
        return q + " at " + "(" + rx + "," + ry + ")";
    }
    
    public static void main(String[] args)
    {
        double x = Double.parseDouble(args[0]);
        double y = Double.parseDouble(args[1]);
        Charge c1 = new Charge(.51, .63, 21.3);
        Charge c2 = new Charge(.13, .94, 81.9);
        double v1 = c1.potentialAt(x,y);
        double v2 = c2.potentialAt(x,y);
        StdOut.println(c1);
        StdOut.println(c2);
        StdOut.println(v1 + v2);
    }
}
