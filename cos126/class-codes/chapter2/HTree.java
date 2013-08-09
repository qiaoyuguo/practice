public class HTree
{
    public static void draw(int n, double sz, double x, double y)
    {
        if(n == 0) return ;
        double x0 = x - sz / 2;
        double x1 = x + sz / 2;
        double y0 = y - sz / 2;
        double y1 = y + sz / 2;

        StdDraw.line(x0, y, x1, y);
        StdDraw.line(x0, y0, x0, y1);
        StdDraw.line(x1, y0, x1, y1);
        
        draw(n-1, sz/2, x0, y0);
        draw(n-1, sz/2, x0, y1);
        draw(n-1, sz/2, x1, y0);
        draw(n-1, sz/2, x1, y1);
    }

    public static void main(String[] args)
    {
        int n = Integer.parseInt(args[0]);
        draw(n, .5, .5, .5);
    }
}
