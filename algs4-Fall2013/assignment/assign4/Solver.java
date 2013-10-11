import java.util.Iterator;
public class Solver {
    private class SearchNode 
    {
        private Board brd;
        private int moves;
        //private int priority;
        private SearchNode prev;
    }
    private Queue<SearchNode> initQueue;
    private Queue<SearchNode> twinQueue;
    private Queue<SearchNode> nodeQueue = new Queue<SearchNode>();
    private Queue<SearchNode> GetSolution(Board initial)
    {
        Queue<SearchNode> queue = new Queue<SearchNode>();
        MinPQ<SearchNode> pq = new MinPQ<SearchNode>();
        SearchNode node = new SearchNode();
        node.brd = initial;
        node.moves = 0;
        //node.priority = initial.manhattan();
        node.prev = null;
        pq.insert(node);
        SearchNode curNode = null;
        while(!pq.isEmpty())
        {
            curNode = pq.delMin();
            if(curNode.brd.isGoal())
                break;
            Iterable<Board> qe= curNode.brd.neighbors();
            Iterator it = qe.iterator();
            while(it.hasNext())
            {
                node.brd = (Board)it.next();  
                node.moves = curNode.moves + 1;
                node.prev = curNode;
                //node.priority = node.brd.manhattan();
                queue.enqueue(node);
            }
        }
        if(queue.isEmpty())
            return null;
        else
        {
            do 
            {
                queue.enqueue(curNode);
                curNode = curNode.prev;
            }while(curNode != null);
            return queue;
        }
            
    }
    public Solver(Board initial)            // find a solution to the initial board (using the A* algorithm)
    {
        initQueue = GetSolution(initial);
        twinQueue = GetSolution(initial.twin());
    }
    public boolean isSolvable()             // is the initial board solvable?
    {
        if(initQueue != null || twinQueue != null)
            return true;
        else
            return false;
    }
    public int moves()                      // min number of moves to solve initial board; -1 if no solution
    {
        if(initQueue != null)
            return initQueue.peek().moves;
        else if(twinQueue != null)
            return twinQueue.peek().moves;
        else
            return -1;
    }
    public Iterable<Board> solution()       // sequence of boards in a shortest solution; null if no solution
    {
        Queue<Board> queue = new Queue<Board>();
        if(initQueue != null)
            nodeQueue = initQueue;
        else if(twinQueue != null)
            nodeQueue = twinQueue;
        else
            return null;

        for(SearchNode node: nodeQueue)
        {
            queue.enqueue(node.brd);
        }
        return queue;
    }
    public static void main(String[] args)  // solve a slider puzzle (given below)
    {
        In in = new In(args[0]);
        int N = in.readInt();
        int [][]blocks = new int[N][N];
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
            {
                blocks[i][j] = in.readInt();
            }

        Board brd = new Board(blocks);
        Solver slv = new Solver(brd);
        Iterable<Board> queue = slv.solution();
        Iterator it = queue.iterator();
        StdOut.printf("Minimum number of moves = %d\n", slv.moves());
        while(it.hasNext())
        {
            StdOut.println(it.next());
        }
    }
}
