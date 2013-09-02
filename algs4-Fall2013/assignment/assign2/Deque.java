import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements  Iterable<Item> 
{
    private int N;
    private Node first;
    private Node last;

    private class Node
    {
        private Item item;
        private Node next;
        private Node prev;
    }

    private boolean check() 
    {
        if(N == 0)
        {
            if(first != null || last != null)
                return false;
        }
        else if(N == 1)
        {
            if(first == null || last == null || first != last) return false;
            if(first.next != null || last.next != null) return false;
            if(first.prev != null || last.prev != null) return false;
        }
        else 
        {
            if(first.next == null || last.next != null) return false;
            if(first.prev != null || last.prev == null) return false;
        }

        int numberOfNodes = 0;
        for(Node x = first; x != null; x = x.next)
        {
            numberOfNodes++;
        }
        if(numberOfNodes != N) return false;

        return true;
    }

    public Deque()
    {
        N = 0;
        first = null;
        last = null;
        assert check();
    }

    public boolean isEmpty()
    {
        return first == null && last == null;
    }

    public int size()
    {
        return N;
    }

    public void addFirst(Item item)
    {
        Node oldfirst = first;
        first = new Node();
        first.item = item;
        first.next = oldfirst;
        first.prev = null;
        if(size() == 0)
            last = first;
        else 
        {
            oldfirst.prev = first;
        }
        N++;
        assert check();
    }

    public void addLast(Item item)
    {
        Node oldlast = last;
        last = new Node();
        last.item = item;
        last.next = null;
        last.prev = null;
        if(size() == 0)
        {
            first = last;
        }
        else
        {
            oldlast.next = last;
            last.prev = oldlast;
        }
        N++;
        assert check();
    }

    public Item removeFirst()
    {
        if(isEmpty())
            throw new NoSuchElementException("Deque underflow");
        Item item = first.item;
        Node oldfirst = first;
        first = first.next;
        if(size() == 1)
            last = null;
        else
        {
            first.prev = null;
        }
        N--;
        oldfirst = null;
        return item;
    }

    public Item removeLast()
    {
        if(isEmpty())
            throw new NoSuchElementException("Dequeue underflow");
        Item item = last.item;
        Node oldlast = last;
        last = last.prev;
        if(size() == 1)
            first = null;
        else
        {
            last.next = null;
        }
        N--;
        oldlast = null;
        return item;
    }

    public Iterator<Item> iterator()
    {
        return new ListIterator();
    }

    private class ListIterator implements Iterator<Item>
    {
        private Node current = first;
        public boolean hasNext() { return current != null;}
        public void remove() {throw new UnsupportedOperationException();}
        public Item next()
        {
            if(!hasNext()) throw new NoSuchElementException();
            Item item = current.item;
            current = current.next;
            return item;
        }
    }

    public static void main(String[] args)
    {
        Deque<String> s = new Deque<String>();
        while(!StdIn.isEmpty())
        {
            String item = StdIn.readString();
            if(!item.equals("-")) s.addLast(item);
            else if(!s.isEmpty()) StdOut.print(s.removeLast() + " ");
        }
        StdOut.println("(" + s.size() + " left on stack)");
    }
}
