package main

import "fmt"
import "os"

func main() {
	fmt.Println(os.Getenv("HOME"))

	os.Setenv("AAA", "000")
	fmt.Println("AAA: ", os.Getenv("AAA"))

	os.Setenv("AAA", "")
	//fmt.Println("AAA: ", os.Getenv("AAA"))

	for _, e := range os.Environ() {
		fmt.Println(e)
	}
}

