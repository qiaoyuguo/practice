public class PercolationStats {
   
   private double []percNumbers;
   public PercolationStats(int N, int T)    // perform T independent computational experiments on an N-by-N grid
   {
   		percNumbers = new double[T];
   		for(int k = 0; k < T; k++)
   		{
   			int count = 0;
   			Percolation pct = new Percolation( N);
   			while(!pct.percolates())
   			{
   				int i = StdRandom.uniform(N)+1;
   				int j = StdRandom.uniform(N)+1;
   				if(!pct.isOpen(i,j))
   				{
   					++count;
   					pct.open(i,j);
   				}
   			}
   			percNumbers[k] = (double)count/(N*N);
   		}
   }
   public double mean()                     // sample mean of percolation threshold
   {
   		double sum = 0;
   		for(int i = 0; i < percNumbers.length; i++)
   			sum += percNumbers[i];
   		return sum/percNumbers.length;
   }
   public double stddev()                   // sample standard deviation of percolation threshold
   {
   		double sum = 0;
   		double mn = mean();
   		for(int i = 0; i < percNumbers.length; i++)
   		{
   			double tmp = percNumbers[i] - mn;
   			sum += tmp * tmp;
   		}
   		if(percNumbers.length <= 1)
   			return 0;
   		else
   			return Math.sqrt(sum / (percNumbers.length - 1));
   }
   public double confidenceLo()            // low end of 95% confidence interval
   {
   		double mn = mean();
   		double sdv = stddev();
   		return (mn-1.96*sdv/(Math.sqrt(percNumbers.length)));
   }
   public double confidenceHi()           // high end of 95% confidence interval
   {
   		double mn = mean();
   		double sdv = stddev();
   		return (mn+1.96*sdv/(Math.sqrt(percNumbers.length)));   
   } 
   private static void printResult(int N, int T)
   {
  		PercolationStats pst = new PercolationStats(200, 100);
  		System.out.println("mean()   =" + pst.mean());
  		System.out.println("stddev() =" + pst.stddev());
  		System.out.println("confidenceLow() = " + pst.confidenceLo());
  		System.out.println("confidenceHigh() = " + pst.confidenceHi());
   }
   public static void main(String[] args)   // do unit testing of this class
   {
           int N = Integer.parseInt(args[0]);
           int T = Integer.parseInt(args[1]);
	   printResult(N,T);
   }
}
