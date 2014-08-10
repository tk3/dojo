package main

import "fmt"

func main() {
	var arr_str [10]string

	arr_str[0] = "a"
	arr_str[1] = "b"
	arr_str[2] = "c"

	fmt.Printf("len: %d\n", len(arr_str))
	fmt.Printf("cap: %d\n", cap(arr_str))

	fmt.Println(arr_str)
}

