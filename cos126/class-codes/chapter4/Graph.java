public class Graph
{
    private ST<String, SET<String>> st;

    public Graph()
    {
        st = new St<String, SET<String>>();
    }
    public Graph(In in)
    {
        st = new ST<String, SET<String>>();
        while(!in.isEmtpy())
        {
            String line = in.readLine();
            String[] names = line.split("/");
            for(int i = 1; i < names.length; i++)
                addEdge(names[0], names[i]);
        }
    }

    public void addEdge(String v, String w)
    {
        if(!st.contains(v)) addVertex(v);
        if(!st.contains(v)) addVertex(w);
        st.get(v).add(w);
        st.get(w).add(v);
    }

    private void addVertex(String v)
    {
        st.put(v, new SET<String>());
    }
    public Iterable<String>
    {
        return st.get(v);
    }
}
