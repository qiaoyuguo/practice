public class ThreeSplitSeq implements Sequence
{
   private final double[] c;

   public ThreeSplitSeq(int maxN)
   {
      c = new double[maxN+1];
      for(int N= 0; N < 3; N++)
          c[N] = 1;
      for (int N = 3; N <= maxN; N++)
         c[N] = N + c[N/3] * 3;
   }

   public double eval(int N)
   {  return c[N];  }

   public static void main(String[] args)
   {
      int maxN = Integer.parseInt(args[0]);
      ThreeSplitSeq m = new ThreeSplitSeq(maxN);
      Values.show(m, maxN);
   }
}
