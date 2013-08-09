//java NBody 157788000.0 25000.0 < planets.txt
public class NBody
{
    public static double distance(double deltax, double deltay)
    {
        return Math.sqrt(deltax * deltax + deltay * deltay);
    }
    public static void main(String[] args)
    {
        double totalTime = Double.parseDouble(args[0]);
        double deltaTime = Double.parseDouble(args[1]);

        int bodyNum = StdIn.readInt();
        double univRadius = StdIn.readDouble();

        double[] xpos = new double[bodyNum];
        double[] ypos = new double[bodyNum];
        double[] vx = new double[bodyNum];
        double[] vy = new double[bodyNum];
        double[] mass = new double[bodyNum];
        String[] imageName = new String[bodyNum];

        for(int i = 0; i < bodyNum; i++)
        {
            xpos[i] = StdIn.readDouble();
            ypos[i] = StdIn.readDouble();
            vx[i] = StdIn.readDouble();
            vy[i] = StdIn.readDouble();
            mass[i] = StdIn.readDouble();
            imageName[i] = StdIn.readString();
        }


        StdDraw.setXscale(-univRadius, univRadius);
        StdDraw.setYscale(-univRadius, univRadius);
        StdAudio.play("2001.mid");

        double G = 6.67e-11;
        for(double t = 0; t < totalTime; )
        {
            StdDraw.picture(0,0, "starfield.jpg");
            for(int i = 0; i < bodyNum; i++)
            {
                StdDraw.picture(xpos[i],ypos[i],imageName[i]);
            }
            for(int i = 0; i < bodyNum; i++)
            {
                double ax = 0.0;
                double ay = 0.0;
                for(int j = 0; j < bodyNum; j++)
                {
                    if( j != i)
                    {
                        double deltax = xpos[j] - xpos[i];
                        double deltay = ypos[j] - ypos[i];
                        double r = distance(deltax, deltay);
                        ax += G * mass[j] * deltax / (r*r*r);
                        ay += G * mass[j] * deltay / (r*r*r);
                    }
                }
                vx[i] += deltaTime * ax;
                vy[i] += deltaTime * ay;
                xpos[i] += deltaTime * vx[i];
                ypos[i] += deltaTime * vy[i];
            }
            StdDraw.show(2);
            t += deltaTime;
            if(t >= totalTime)
            {
                System.out.println(bodyNum);
                System.out.println(univRadius);
                for(int i = 0; i < bodyNum; i++)
                {
                    System.out.println(String.format("%7.4e %7.4e %7.4e %7.4e %7.4e", xpos[i],ypos[i],vx[i],vy[i],mass[i],imageName[i] ));
                }
            }
        }

    }
}
