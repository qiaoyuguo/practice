public class LinkedStackOfStrings
{
    private Node first = null;
    private class Node {
        private String item;
        private Node next;
    }

    public boolean isEmpty() {return first == null;}
    public void push(String item)
    {
        Node second = first;
        first = new Node();
        first.item = item;
        first.next = second;
    }
    public String pop()
    {
        String item = first.item;
        first = first.next;
        return item;
    }
}
