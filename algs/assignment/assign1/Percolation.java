//import algs.QuickFindUF;
public class Percolation {
    private boolean [][]grid;
    private QuickFindUF quf;
  
    public Percolation(int N)              // create N-by-N grid, with all sites blocked
    {
        quf = new QuickFindUF(N*N);
        grid = new boolean[N][N];
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                grid[i][j] = false;
    }

    public int conv(int i, int j)
    {
        return i *  grid.length + j;
    }
    public void open(int i, int j)         // open site (row i, column j) if it is not already
    {
    	if(isOpen(i,j))
    		return;
        grid[i][j] = true;
        int []direct  = {-1, 1};
        for(int k = 0; k <= 1; k++)
        {
            int x = i + direct[k];
            int y = j;
            if(x < 0 || y <0 || x >= grid.length || y >= grid.length)
                continue;
            if(isOpen(x,y))
                quf.union(conv(x,y), conv(i,j));
        }
        for(int k = 0; k <= 1; k++)
        {
            int x = i;
            int y = j+ direct[k];
            if(x < 0 || y <0 || x >= grid.length || y >= grid.length)
                continue;
            if(isOpen(x, y))
                quf.union(conv(x,y), conv(i,j));
        }
    }
    
    public boolean isOpen(int i, int j)    // is site (row i, column j) open?
    {
        return grid[i][j] == true;
    }
    public boolean isFull(int i, int j)    // is site (row i, column j) full?
    {
        for(int k = 0; k < grid.length; k++)
            if(quf.connected(k, conv(i,j) ))
                return true;
        return false;
    }
    public boolean percolates()            // does the system percolate?
    {
        int n = grid.length;
        for(int i = 0; i < n; i++)
            if(isFull(n-1, i))
                return true;
        return false;
    }

}
