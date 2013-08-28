//import algs.QuickFindUF;
public class Percolation {
    private boolean [][]grid;
    private WeightedQuickUnionUF quf;
  
    public Percolation(int N)              // create N-by-N grid, with all sites blocked
    {
        int n = N + 1;
        quf = new WeightedQuickUnionUF(n*n);
        grid = new boolean[n][n];
        for(int i = 1; i < n; i++)
            for(int j = 1; j < n; j++)
                grid[i][j] = false;
        grid[0][0] = false; // virtual top site
        grid[0][1] = false; // virtual bottom site
    }

    private int conv(int i, int j)
    {
        return i * grid.length + j;
    }
    public void open(int i, int j)         // open site (row i, column j) if it is not already
    {
    	if(isOpen(i,j))
    		return;
        grid[i][j] = true;
        if(i == 1)
        {
            grid[0][0] = true;
            quf.union(0, conv(i,j));
        }
        if(i == grid.length - 1)
        {
            grid[0][1] = true;
            quf.union(1, conv(i,j));
        }

        int []direct  = {-1, 1};
        for(int k = 0; k <= 1; k++)
        {
            int x = i + direct[k];
            int y = j;
            if(x <= 0 || y <=0 || x >= grid.length || y >= grid.length)
                continue;
            if(isOpen(x,y))
                quf.union(conv(x,y), conv(i,j));
        }
        for(int k = 0; k <= 1; k++)
        {
            int x = i;
            int y = j+ direct[k];
            if(x <= 0 || y <=0 || x >= grid.length || y >= grid.length)
                continue;
            if(isOpen(x, y))
                quf.union(conv(x,y), conv(i,j));
        }
    }
    
    public boolean isOpen(int i, int j)    // is site (row i, column j) open?
    {
        int len = grid.length;
        if (i <= 0 || i >= len) 
            throw new IndexOutOfBoundsException("row index " + i + " must be between 0 and " + (len-1));
        if(j <= 0 || j >= len)
            throw new IndexOutOfBoundsException("column index " + i + " must be between 0 and " + (len-1));
        return grid[i][j] == true;
    }
    public boolean isFull(int i, int j)    // is site (row i, column j) full?
    {
        int len = grid.length;
        if (i <= 0 || i >= len) 
            throw new IndexOutOfBoundsException("row index " + i + " must be between 1 and " + (len-1));
        if(j <= 0 || j >= len)
            throw new IndexOutOfBoundsException("column index " + i + " must be between 1 and " + (len-1));
        if(!isOpen(i,j))
            return false;
        return quf.connected(0, conv(i,j));
    }
    public boolean percolates()            // does the system percolate?
    {
        return quf.connected(0,1);
    }
    private static String bool2str(boolean b) 
    {
        if(b)
            return "true";
        else
            return "false";
    }
    public static void main(String[] args)
    {
        In in = new In(args[0]);
        int N = in.readInt();         // N-by-N percolation system
        Percolation perc = new Percolation(N);
        while (!in.isEmpty()) {
            int i = in.readInt();
            int j = in.readInt();
            perc.open(i, j);
        }

        for(int i = N+1+1; i < (N+1)*(N+1); i++)
        {
            for(int j = i+1; j< (N+1)*(N+1); j++)
            {
                System.out.println(i + " " + j + " " + bool2str(perc.quf.connected(i,j)));
            }
        }

        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                System.out.println(i + " " + j + " " + bool2str(perc.isFull(i,j)));
    }

}
