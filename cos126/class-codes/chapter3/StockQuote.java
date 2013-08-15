public class StockQuote
{
    public static void main(String[] args)
    {
        String name = "http://www.thestreet.com/quote/";
        In in = new In(name + args[0] + ".html");
        String input = in.readAll();
        int start = input.indexOf("topTradeInfo",0);
        int from = input.indexOf("price-tabs", start);
        int to = input.indexOf("</span>", from);

        String price = input.substring(from + 12, to);
        StdOut.println(price);
    }
}
