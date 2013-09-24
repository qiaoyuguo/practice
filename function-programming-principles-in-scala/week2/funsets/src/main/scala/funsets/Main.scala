package funsets

object Main extends App {
  import FunSets._
  println(contains(singletonSet(1), 1))
  val s1 = singletonSet(1)
  val s2 = singletonSet(2)
  val s = union(s1,s2)
  val r = map(s, x=>x*x)
  printSet(s)
  printSet(r)
  
}
