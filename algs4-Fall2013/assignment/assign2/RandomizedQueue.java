import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item>  implements Iterable<Item>
{
    private Item[] a;
    private int N;

    public RandomizedQueue()
    {
        a = (Item[]) new Object[2];
    }

    public boolean isEmpty()
    {
        return N == 0;
    }

    public int size()
    {
        return N;
    }

    private void resize(int capacity)
    {
        assert capacity >= N;
        Item[] temp = (Item[]) new Object[capacity];
        for(int i = 0; i < N; i++)
        {
            temp[i] = a[i];
        }
        a = temp;
    }
    public void enqueue(Item item)
    {
        if(item == null)
            throw new NullPointerException();
        if(N == a.length) resize(2*a.length);
        a[N++] = item;
    }

    public Item dequeue()
    {
        if(isEmpty()) throw new NoSuchElementException("RandomizedQueue underflow");
        int rnd = StdRandom.uniform(N);
        Item swap = a[rnd];
        a[rnd] = a[N-1];
        a[N-1] =  swap;
        Item item = a[N - 1];
        a[N-1] = null;
        N--;
        if(N > 0 && N == a.length/4) resize(a.length/2);
        return item;
    }
    
    public Item sample()
    {
        if(isEmpty()) throw new NoSuchElementException("RandomizedQueue underflow");
        int rnd = StdRandom.uniform(N);
        return a[rnd];
    }
    
    public Iterator<Item> iterator()
    {
        return new ArrayIndexIterator();
    }

    private class ArrayIndexIterator implements Iterator<Item> 
    {
        private int i = 0;
        public boolean hasNext()
        {
            return i < N;
        }
        public void remove()
        {
            throw new UnsupportedOperationException();
        }

        public Item next()
        {
            if(!hasNext()) throw new NoSuchElementException();
            return a[i++];
        }
    }

    public static void main(String[] args)
    {
    }
}
