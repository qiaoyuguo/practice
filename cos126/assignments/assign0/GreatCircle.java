public class GreatCircle
{
    public static double mysin(double angle)
    {
        return Math.sin(Math.toRadians(angle));
    }
    public static double mycos(double angle)
    {
        return Math.cos(Math.toRadians(angle));
    }
    public static void main(String[] args)
    {
        double x1 = Double.parseDouble(args[0]);
        double y1 = Double.parseDouble(args[1]);
        double x2 = Double.parseDouble(args[2]);
        double y2 = Double.parseDouble(args[3]);

        double dist = 60 * Math.toDegrees(Math.acos(mysin(x1)*mysin(x2) +mycos(x1)*mycos(x2)*mycos(y1-y2)));
        System.out.println(dist + " nautical miles");
    }
}
