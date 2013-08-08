public class Quadratic
{
    public static void main(String[] args)
    {
        // Parse coefficients from command-line
        double b = Double.parseDouble(args[0]);
        double c = Double.parseDouble(args[1]);

        // Calculate roots
        double discriminant = b*b - 4.0*c;
        double d = Math.sqrt(discriminant);
        double root1 = (-b + d) / 2;
        double root2 = (-b - d) / 2;

        // Print them out
        System.out.println(root1);
        System.out.println(root2);
    }
}
