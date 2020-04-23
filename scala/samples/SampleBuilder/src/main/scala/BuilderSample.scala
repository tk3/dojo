
case class Book(
  title: String,
  author: String,
  pages: Int,
  price: Double
)

class BookBuilder(
  book:Book = Book("", "", 0, 0.0)
) {
  def build(): Book = {
    book
  }

  def withTitle(title:String):BookBuilder = {
    new BookBuilder(book.copy(title = title))
  }

  def withAuthor(author:String):BookBuilder = {
    new BookBuilder(book.copy(author = author))
  }

  def withPages(pages:Int):BookBuilder = {
    new BookBuilder(book.copy(pages = pages))
  }

  def withPrice(price:Double):BookBuilder = {
    new BookBuilder(book.copy(price = price))
  }
}

object BookBuilder {
  def apply(): BookBuilder = new BookBuilder(book = Book("", "", 0, 0.0))
}

object BuilderSample {

  def main(args: Array[String]): Unit = {
    val book = BookBuilder()
      .withTitle("title aaa")
      .withAuthor("author bbb")
      .withPages(100)
      .withPrice(19.8)
      .build()

    println(s"title: ${book.title}")
    println(s"author: ${book.author}")
    println(s"pages: ${book.pages}")
    println(s"price: ${book.price}")
  }
}