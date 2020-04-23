
import slick.dbio.DBIO
import slick.driver.H2Driver.api._

import scala.concurrent.Await
import scala.concurrent.duration.Duration

object SlickSample {
//  val publishers: TableQuery[Publishers] = TableQuery[Publishers]
//  val authors: TableQuery[Authors] = TableQuery[Authors]
//  val books: TableQuery[Books] = TableQuery[Books]

  def main(args: Array[String]): Unit = {
    val url = "jdbc:h2:mem:test1;DB_CLOSE_DELAY=-1"
    val db = Database.forURL(url, driver = "org.h2.Driver")

    setup(db)

    sampleSelect(db)
    sampleSelectWithWhere(db)
    sampleSelectColumns(db)
    sampleSelectForUpdate(db)
    sampleSelectInnerJoin(db)

    sampleUpdate(db)
  }

  def setup(db: Database): Unit = {
    val setup = DBIO.seq(
      (Authors.schema ++ Publishers.schema ++ Books.schema).create,

      Authors ++= Seq(
        (100, "author user 01", "aaa"),
        (101, "author user 02", "bbb"),
        (102, "author user 03", "ccc")
      ),

      Publishers ++= Seq(
        (200, "publisher 01", "address aa"),
        (201, "publisher 02", "address bb"),
        (202, "publisher 03", "address cc")
      ),

      Books ++= Seq(
        (300, "book title 01", 100L, 200L, "1234567890123", 198.0, 280),
        (301, "book title 01", 100L, 200L, "2234567890123", 1480.0, 480),
        (302, "book title 01", 100L, 200L, "3234567890123", 1980.0, 315),
      )
    )
    val f = db.run(setup)
    Await.result(f, Duration.Inf)
  }

  def sampleSelect(db: Database): Unit = {
    val s = Books.result
    val sql = s.statements.head
    val result = Await.result(db.run(s), Duration.Inf)

    println("-------- sample select --------")
    println(s"sql = $sql")
    println(s"result = $result")
  }

  def sampleSelectWithWhere(db: Database): Unit = {
    val s = Books.filter(_.id > 100L).result
    val sql = s.statements.head
    val result = Await.result(db.run(s), Duration.Inf)

    println("-------- sample select with where --------")
    println(s"sql = $sql")
    println(s"result = $result")
  }

  def sampleSelectColumns(db: Database): Unit = {
    val s = Books.map(row => (row.title, row.price)).result
    val sql = s.statements.head
    val result = Await.result(db.run(s), Duration.Inf)

    println("-------- sample select with where --------")
    println(s"sql = $sql")
    println(s"result = $result")
  }

  def sampleSelectInnerJoin(db: Database): Unit = {
    val s = Books
      .join(Authors)
      .on((books, authors) => books.authorId === authors.id)
      .result
    val sql = s.statements.head
    val result = Await.result(db.run(s), Duration.Inf)

    println("-------- sample select inner join --------")
    println(s"sql = $sql")
    println(s"result = $result")
  }

  def sampleSelectForUpdate(db: Database): Unit = {
    val s = Books.filter(_.id > 100L).forUpdate.result
    val sql = s.statements.head
    val result = Await.result(db.run(s), Duration.Inf)

    println("-------- sample select with where --------")
    println(s"sql = $sql")
    println(s"result = $result")
  }

  def sampleUpdate(db: Database): Unit = {
    val s = Books.filter(_.id === 151L).map(_.title).update("Tokyo")
    val sql = s.statements.head
    val result = Await.result(db.run(s), Duration.Inf)

    val s2 = Books.filter(_.id === 151L).result
    val resultAfterUpdate = Await.result(db.run(s2), Duration.Inf)

    println("-------- sample update --------")
    println(s"sql = $sql")
    println(s"result = $result")
    println(s"result = $resultAfterUpdate")
  }
}
