import java.awt.Color;
public class PhotoMagic
{
    public static Picture transform(Picture picture, LFSR lfsr)
    {
        int width = picture.width();
        int height = picture.height();

        for(int i = 0; i < width; i++)
        {
            for(int j = 0; j < height; j++)
            {
                Color c = picture.get(i,j);
                int red = c.getRed();
                int newRed = lfsr.generate(8)^red;
                int green = c.getGreen();
                int newGreen = lfsr.generate(8)^green;
                int blue = c.getBlue();
                int newBlue= lfsr.generate(8)^blue;
                Color newc = new Color(newRed, newGreen, newBlue);
                picture.set(i,j,newc);
            }
        }
        return picture;
    }

    public static void main(String[] args)
    {
        Picture  pic = new Picture(args[0]);
        String seed = args[1];
        int tap = Integer.parseInt(args[2]);

        LFSR lfsr = new LFSR(seed, tap);
        Picture res = transform(pic, lfsr);
        pic.show();
    }
}
