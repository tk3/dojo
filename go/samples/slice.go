package main

import "fmt"

func main() {
	s := make([]int, 8, 16)

	fmt.Printf("len: %d\n", len(s))
	fmt.Printf("cap: %d\n", cap(s))

	fmt.Println(s)

	s[0] = 10
	fmt.Println(s)

	s1 := append(s, 99)
	fmt.Println(s)
	fmt.Println(s1)

	fmt.Printf("len: %d\n", len(s1))
	fmt.Printf("cap: %d\n", cap(s1))
}

