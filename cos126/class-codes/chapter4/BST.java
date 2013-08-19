public class BST<Key extends Comparable<Key>, Value >
{
    private Node root;

    private class Node
    {
        private Key key;
        private Value val;
        private Node left, right;
        private Node(Key key, Value val)
        {
            this.key = key;
            this.val = val;
        }
    }
    public Value get(Key key)
    {
        return get(root, key);
    }
    public Value get(Node x, Key key)
    {
        if(x == null) return null;
        int cmp = key.compareTo(x.key);
        if(cmp < 0) return get(x.left, key);
        else if(cmp > 0) return get(x.right, key);
        else  return x.val;
    }

    public boolean contains(Key key)
    {
        return (get(key) != null);
    }

    public void put(Key key, Value val)
    {
        root = put(root, key, val);
    }

    public Node put(Node x, Key key, Value val)
    {
    if(x == null) return new Node(key, val);
    int cmp = key.compareTo(x.key);
    if(cmp < 0) x.left = put(x.left, key, val);
    else if(cmp > 0) x.right = put(x.right, key, val);
    else x.val = val;

    return x;
    }
}
