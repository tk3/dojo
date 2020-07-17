
import slick.dbio.{DBIO, Effect}
import slick.driver.H2Driver
import slick.driver.H2Driver.api._
import slick.sql.FixedSqlAction

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
    sampleCount(db)

    sampleUpdate(db)
  }

  def setup(db: Database): Unit = {
    val setup = DBIO.seq(
      (Authors.schema ++ Publishers.schema ++ Books.schema).create,

      Authors ++= Seq(
        (100, "author user 00", "aaa"),
        (101, "author user 01", "bbb"),
        (102, "author user 02", "ccc")
      ),

      Publishers ++= Seq(
        (200, "publisher 00", "address aa"),
        (201, "publisher 01", "address bb"),
        (202, "publisher 02", "address cc")
      ),

      Books ++= Seq(
        (300, "book title 00", 100L, 200L, "1034567890123", 198.0, 36),
        (301, "book title 01", 100L, 200L, "1134567890123", 548.0, 36),
        (302, "book title 02", 100L, 201L, "1234567890123", 980.0, 8),
        (303, "book title 03", 100L, 202L, "1334567890123", 500.0, 48),
        (304, "book title 04", 100L, 202L, "1434567890123", 200.0, 96),

        (305, "book title 05", 101L, 200L, "1534567890123", 168.0, 36),
        (306, "book title 06", 101L, 201L, "1634567890123", 380.0, 12),
        (307, "book title 07", 101L, 201L, "1734567890123", 320.0, 84),
        (308, "book title 08", 101L, 201L, "1834567890123", 220.0, 24),
        (309, "book title 09", 101L, 202L, "1934567890123", 450.0, 60),
        (310, "book title 10", 101L, 202L, "2034567890123", 680.0, 72),

        (311, "book title 11", 102L, 201L, "2134567890123", 790.0, 60),
        (312, "book title 12", 102L, 201L, "2234567890123", 990.0, 48),
        (313, "book title 13", 102L, 201L, "2334567890123", 120.0, 48),
        (314, "book title 14", 102L, 202L, "2434567890123", 520.0, 36),
        (315, "book title 15", 102L, 202L, "2534567890123", 890.0, 24),
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

  def sampleCount(db: Database): Unit = {
    val s = Books.filter(_.id > 100L).length.result
    val sql = s.statements.head
    val result = Await.result(db.run(s), Duration.Inf)

    println("-------- sample select --------")
    println(s"sql = $sql")
    println(s"result = $result")
  }
}
