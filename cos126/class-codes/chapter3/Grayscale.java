import java.awt.Color;

public class Grayscale
{
    public static void main(String[] args)
    {
        Picture pic = new Picture(args[0]);
        for(int x = 0; x < pic.width(); x++)
            for(int y = 0; y < pic.height(); y++)
            {
                Color color = pic.get(x,y);
                Color gray = Luminance.toGray(color);
                pic.set(x, y, gray);
            }
        pic.show();
    }
}
