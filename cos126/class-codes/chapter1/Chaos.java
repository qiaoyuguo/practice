// java Chaos 5000
public class Chaos
{
    public static void main(String[] args)
    {
        int T = Integer.parseInt(args[0]);
        double[] cx = {0.000, 1.000, 0.500};
        double[]  cy = {0.000, 0.000, 0.866};
        double x = 0.0, y = 0.0;
        for(int t = 0; t < T; t++)
        {
            int r = (int)(Math.random() * 3);
            x = (x + cx[r]) / 2.0;
            y = (y + cy[r]) / 2.0;
            StdDraw.point(x,y);
        }
    }
}
