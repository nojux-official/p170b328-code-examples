object Main {
  private def getVector: Seq[Int] = 0 to 20

  def main(args: Array[String]): Unit = {
    val dataVector = getVector
    // Filter only even numbers
    val filteredVector = dataVector.filter(_ % 2 == 0)
    // Map to squares
    val squaredVector = filteredVector.map(x => x * x)
    // Reduce to sum
    val sum = squaredVector.reduce(_ + _)

    println(s"$sum")
  }
}
