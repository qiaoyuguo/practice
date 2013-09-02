//import algs.QuickFindUF;
public class Percolation {
    private boolean [][]grid;
    private WeightedQuickUnionUF quf;
    private WeightedQuickUnionUF quf2;
  
    public Percolation(int N)              // create N-by-N grid, with all sites blocked
    {
        int n = N + 1;
        quf = new WeightedQuickUnionUF(n*n);
        quf2 = new WeightedQuickUnionUF(n*n);
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
            quf2.union(0, conv(i,j));
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
            {
                quf.union(conv(x,y), conv(i,j));
                quf2.union(conv(x,y), conv(i,j));
            }
        }
        for(int k = 0; k <= 1; k++)
        {
            int x = i;
            int y = j+ direct[k];
            if(x <= 0 || y <=0 || x >= grid.length || y >= grid.length)
                continue;
            if(isOpen(x, y))
            {
                quf.union(conv(x,y), conv(i,j));
                quf2.union(conv(x,y), conv(i,j));
            }
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
        return quf2.connected(0, conv(i,j));
    }
    public boolean percolates()            // does the system percolate?
    {
        return quf.connected(0,1);
    }
    private static String bool2str(boolean b) 
    {
        if(b)
            return "t";
        else
            return "f";
    }
    private boolean getTop()
    {
        return grid[0][0];
    }
    private boolean getBottom()
    {
        return grid[0][1];
    }
    public static void main(String[] args)
    {
        In in = new In(args[0]);
        int N = in.readInt();         // N-by-N percolation system
        int count = 0;
        Percolation perc = new Percolation(N);
        while (!in.isEmpty()) {
            int r = in.readInt();
            int c = in.readInt();
            perc.open(r, c);
            System.out.println("r:"+r+"c:"+c);
            ++count;

            System.out.println("open condition:");
            for(int i = 1; i <= N; i++)
            {
                for(int j = 1; j <= N; j++)
                    System.out.print(bool2str(perc.isOpen(i,j)) + " ");
                System.out.println();
            }
            System.out.println("top:" + bool2str(perc.getTop()));
            System.out.println("bottom:" + bool2str(perc.getBottom()));


            System.out.println("full condition:");
            for(int i = 1; i <= N; i++)
            {
                for(int j = 1; j <= N; j++)
                    System.out.print(bool2str(perc.isFull(i,j)) + " ");
                System.out.println();
            }

            if(count == 4)
            {
                break;
            }
        }

    }

}
