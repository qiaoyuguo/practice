public class Complex
{
    private final double re;
    private final double im;

    public Complex(double real, double imag)
    {
        re = real;
        im = imag;
    }

    public String toString()
    {
        return re + " + " + im + "i";
    }

    public double abs()
    {
        return Math.sqrt(re * re + im * im);
    }

    public Complex plus(Complex b)
    {
        double real = re + b.re;
        double imag = im + b.im;
        return new Complex(real, imag);
    }
    public Complex times(Complex b)
    {
        double real = re * b.re - im * b.im;
        double imag = re * b.im + im * b.re;
        return new Complex(real, imag);
    }

    public static void main(String[] args)
    {
        Complex a = new Complex(3.0, 4.0);
        Complex b = new Complex(-2.0, 3.0);
        Complex c = a.times(b);
        StdOut.println("a = "+ a);
        StdOut.println("b = "+ b);
        StdOut.println("c = " +c);

    }
}
