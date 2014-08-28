package main

import "fmt"

type Book struct {
    title string
    author string
    price int
}

func main() {
	var b Book
	b.title = "Sample 01"
	b.author = "Foo Bar"
	b.price = 200
	fmt.Println(b)

	var v struct {
		x int
		y int
	}
	v.x = 10
	v.y = 20
	fmt.Println(v)
}
