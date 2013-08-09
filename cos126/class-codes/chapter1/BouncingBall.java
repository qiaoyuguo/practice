public class BouncingBall
{
    public static void main(String[] args)
    {
        double rx = .480, ry = .860;
        double vx = .015, vy = .023;
        double radius = .05;

        StdDraw.setXscale(-1.0, +1.0);
        StdDraw.setYscale(-1.0, +1.0);

        while(true)
        {
            if(Math.abs(rx + vx) + radius > 1.0) vx = -vx;
            if(Math.abs(ry + vy) + radius > 1.0) vy = -vy;

            rx = rx + vx;
            ry = ry + vy;

            StdDraw.setPenColor(StdDraw.GRAY);
            StdDraw.filledSquare(0.0,0.0,1.0);
            StdDraw.setPenColor(StdDraw.BLACK);
            StdDraw.filledCircle(rx, ry, radius);
            StdDraw.show(50);
        }
    }
}
