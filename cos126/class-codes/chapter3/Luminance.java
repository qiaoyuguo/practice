import java.awt.Color;

public class Luminance
{
    public static double lum(Color c)
    {
        int r = c.getRed();
        int g = c.getGreen();
        int b = c.getBlue();
        return .299*r + .587*g + .114*b;
    }
    public static boolean compatible(Color a, Color b)
    {
        return Math.abs(lum(a) - lum(b)) >= 128.0;
    }
    public static Color toGray(Color c)
    {
        int y = (int)Math.round(lum(c));
        Color gray = new Color(y, y, y);
        return gray;
    }
}
