package main

import "fmt"

func sample1() {
	fmt.Println("sample1 --------")

	val := []int{10, 20, 30, 40}

	fmt.Println(val)
	fmt.Printf("len: %d\n", len(val))
	fmt.Printf("cap: %d\n", cap(val))

	s := val[:]

	fmt.Println(s)
	fmt.Printf("len: %d\n", len(val))
	fmt.Printf("cap: %d\n", cap(val))
}

func sample2() {
	fmt.Println("sample2 --------")

	val := []int{10, 20, 30, 40}

	s1 := val[2:]
	fmt.Println(s1)

	s2 := val[2:3]
	fmt.Println(s2)
}

func sample3() {
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

func main() {
	sample1()
	sample2()
}

