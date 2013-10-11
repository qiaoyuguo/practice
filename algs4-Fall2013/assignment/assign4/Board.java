import java.util.Iterator;

public class Board {
    private int N;
    private int [][]board;
    public Board(int[][] blocks)           // construct a board from an N-by-N array of blocks
    {
        N = blocks.length;
        board = new int[N][N];
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                board[i][j] = blocks[i][j];
    }
                                           // (where blocks[i][j] = block in row i, column j)
    public int dimension()                 // board dimension N
    {
        return N;
    }
    public int hamming()                   // number of blocks out of place
    {
        int count = 0;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
            {
                if(i == N-1 && j == N-1)
                {
                    //if(board[i][j] != 0)
                    //   ++count;
                }
                else if(board[i][j] != i*N + j + 1)
                    ++count;
            }
        return count;
    }
    public int manhattan()                 // sum of Manhattan distances between blocks and goal
    {
        int count = 0;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                if(board[i][j] != 0)
                {
                    int x = (board[i][j]-1)/N;
                    int y = (board[i][j]-1)%N;
                    count += Math.abs(x-i) + Math.abs(y-j);
                }
        return count;
    }
    public boolean isGoal()                // is this board the goal board?
    {
        for(int i = 0; i < N; i++)
            for(int  j = 0; j < N; j++)
            {
                if(i == N && j == N)
                {
                    if(board[i][j] != 0)
                        return false;
                }
                else if(board[i][j] != i+j+1)
                    return false;
            }
        return true;
    }
    public Board twin()                    // a board obtained by exchanging two adjacent blocks in the same row
    {
        Board newBoard = new Board(board);
        int i = 0;
        int j1= 0, j2 = 1;
        if(newBoard.board[i][j1] == 0)
            j1 = 2;
        else if(newBoard.board[i][j2] == 0)
            j2 = 2;
        int tmp = newBoard.board[i][j1];
        newBoard.board[i][j1] = newBoard.board[i][j2];
        newBoard.board[i][j2] = tmp;

        return newBoard;
    }
    public boolean equals(Object y)        // does this board equal y?
    {
        if(y == this) return true;
        if(y == null) return false;
        if(y.getClass() != this.getClass()) return false;
        Board that = (Board)y;
        if(this.N != that.N)
            return false;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                if(board[i][j] != that.board[i][j] )
                    return false;
        return true;
    }
    public Iterable<Board> neighbors()     // all neighboring boards
    {
        Queue<Board> queue = new Queue<Board>();
        //StdOut.println("N =" + N);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N-1; j++)
            {
                if(board[i][j] == 0 || board[i][j+1] == 0)
                    continue;
                Board newBoard = new Board(board);
                //StdOut.println(newBoard);
                int tmp = newBoard.board[i][j];
                newBoard.board[i][j] = newBoard.board[i][j+1];
                newBoard.board[i][j+1] = tmp;
                queue.enqueue(newBoard);
            }

        return queue;
    }
    public String toString()               // string representation of the board (in the output format specified below)
    {
        StringBuilder s = new StringBuilder();
        s.append(N + "\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if(board[i][j] != 0)
                {
                    s.append(String.format("%2d ", board[i][j]));
                }
                else
                {
                    s.append(String.format(" "));
                }
            }
            s.append("\n");
        }
        return s.toString();
    }
    public static void main(String[] args)
    {
        int [][]blocks = new int[][]{{0, 1,3},{4,2,5},{7,8,6}};
        int [][]blocks1 = new int[][]{{0, 1,3},{4,2,5},{7,8,6}};
        int [][]blocks2 = new int[][]{{1, 2,3},{4,5,6},{7,8,0}};
        StdOut.println(blocks);
        Board brd = new Board(blocks);
        Board brd1 = new Board(blocks1);
        Board brd2 = new Board(blocks2);
        StdOut.println(brd);
        StdOut.println(brd.dimension() == 3);
        StdOut.println(brd.hamming() + " solution should be "+  5);
        StdOut.println(brd.manhattan() + " solution should be "+ 10);
        StdOut.println(brd.isGoal() + " solution should be " +  false);
        StdOut.println(brd2.isGoal() + " solution should be "+ true);
        StdOut.println(brd.equals(brd1) + " solution should be "+ true);
        StdOut.println(brd.equals(brd2) + " solution should be "+ false);
        StdOut.print(brd2);

        /*
        Iterable<Board> qe= brd.neighbors();
        Iterator it = qe.iterator();
        StdOut.println(it.hasNext());
        while(it.hasNext())
        {
            StdOut.println(it.next());
        }
        */
    }

}
