public class Values
{ 
   public static void  print(Sequence f, int maxN)
   {
       for (int N = 0; N < maxN; N++)
	   StdOut.printf("%10.6f %10.6f\n", f.eval(N), N*f.eval(N));
   }

   public static void  show(Sequence f, int maxN)
   {
      print(f, 15);

      double max = 0;
      for (int N = 0; N < maxN; N++)
	  if (f.eval(N)>max) max = f.eval(N);
      for (int N = 0; N < maxN; N++)
      {
         double x = 1.0*N/maxN;
         double y = 1.0*f.eval(N)/max;
	 StdDraw.filledCircle(x, y, .004);
      }

      StdDraw.show();
   }

}
