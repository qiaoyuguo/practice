public class Insertion
{
    public static void sort(double[] a)
    {
        int  N = a.length;
        for(int i = 1; i < N; i++)
            for(int j = i; j >0; --j)
                if(a[j-1] > a[j])
                    exch(a, j-1, j);
                else
                    break;
    }
    private static void exch(double[] a, int i, int j)
    {
        double swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }
    private static void printArray(double[] a)
    {
        for(int i = 0; i < a.length; i++)
        {
            if(i > 0)
                System.out.print(" ");
            System.out.print(a[i]);
        }
        System.out.println();
    }


    public static void main(String[] args)
    {
        int n = 10;
        double[] a = new double[n];
        for(int i = 0; i < n; i++)
            a[i] = Math.random();
        printArray(a);
        sort(a);
        printArray(a);
    }
}
