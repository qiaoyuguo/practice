package recfun
import common._

object Main {
  def main(args: Array[String]) {
    /*
    println("Pascal's Triangle")
    for (row <- 0 to 10) {
      for (col <- 0 to row)
        print(pascal(col, row) + " ")
      println()	
    }
    */
    /*
    if(balance("(if (zero? x) max (/ 1 x))".toList))
    	println("True")
    else
    	println("False")
    * 
    */
    println(countChange(4, List(1,2)))
    
  }

  /**
   * Exercise 1
   */
  def pascal(c: Int, r: Int): Int = {
    if(c == 0) 1
    else if(c == r) 1
    else pascal(c-1,r-1) + pascal(c, r-1)
  }

  /**
   * Exercise 2
   */
  def isBalance(chars: List[Char], count: Int) : Boolean = {
      if(chars.isEmpty) (count == 0)
      else if(chars.head == '(') isBalance(chars.tail, count+1)
      else if((chars.head == ')') && (count > 0)) isBalance(chars.tail, count-1)
      else if((chars.head == ')') && (count <= 0))  false
      else isBalance(chars.tail, count)
    }
  
  def balance(chars: List[Char]): Boolean = {
    isBalance(chars, 0)
  }

  /**
   * Exercise 3
   */
  def countChange(money: Int, coins: List[Int]): Int = {
    if(money < 0) 0
    else if(money == 0 && coins.isEmpty) 1
    else if(coins.isEmpty) 0
    else countChange(money - coins.head, coins) + countChange(money , coins.tail)
  }
}
