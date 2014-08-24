package main

import "fmt"

var total int

func func1(n int) {
	total += n
}

func main() {
	go func1(10)

	fmt.Println(total)
}

