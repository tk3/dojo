import slick.driver.H2Driver.api._
import slick.lifted.{ProvenShape, ForeignKeyQuery}

class Authors(tag: Tag) extends Table[(Long, String, String)](tag, "AUTHORS") {
  def id: Rep[Long] = column[Long]("ID", O.PrimaryKey)
  def name: Rep[String] = column[String]("NAME")
  def biography: Rep[String] = column[String]("BIOGRAPHY")

  override def * : ProvenShape[(Long, String, String)] = (id, name, biography)
}

object Authors extends TableQuery(new Authors(_))

class Publishers(tag: Tag) extends Table[(Long, String, String)](tag, "PUBLISHERS") {
  def id: Rep[Long] = column[Long]("ID", O.PrimaryKey)
  def name: Rep[String] = column[String]("NAME")
  def address: Rep[String] = column[String]("ADDRESS")

  override def * : ProvenShape[(Long, String, String)] = (id, name, address)
}

object Publishers extends TableQuery(new Publishers(_))

class Books(tag: Tag) extends Table[(Long, String, Long, Long, String, Double, Long)](tag, "BOOKS") {
  def id: Rep[Long] = column[Long]("ID", O.PrimaryKey)
  def title: Rep[String] = column[String]("TITLE")
  def authorId: Rep[Long] = column[Long]("AUTHOR_ID")
  def publisherId: Rep[Long] = column[Long]("PUBLISHER_ID")
  def isbn: Rep[String] = column[String]("ISBN")
  def price: Rep[Double] = column[Double]("PRICE")
  def pages: Rep[Long] = column[Long]("PAGES")

  override def * : ProvenShape[(Long, String, Long, Long, String, Double, Long)] =
    (id, title, authorId, publisherId, isbn, price, pages)

  def author: ForeignKeyQuery[Authors, (Long, String, String)] =
    foreignKey("AUTHOR_FK", authorId, TableQuery[Authors])(_.id)

  def publisher: ForeignKeyQuery[Publishers, (Long, String, String)] =
    foreignKey("PUBLISHER_FK", publisherId, TableQuery[Publishers])(_.id)
}

object Books extends TableQuery(new Books(_))

