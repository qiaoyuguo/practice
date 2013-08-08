public class Newton
{
    public static double sqrt(double c)
    {
        double epsilon = 1e-15;
        if (c < 0) return Double.NaN;
        double t = c;
        while (Math.abs(t - c/t) > epsilon * t)
            t = (c/t + t) / 2.0;
        return t;
    }

    public static void main(String[] args)
    {
        double[] a = new double[args.length];
        for(int i = 0; i < args.length; i++)
            a[i] = Double.parseDouble(args[i]);
        for(int i = 0; i < a.length; i++)
            System.out.println(sqrt(a[i]));

    }
}
