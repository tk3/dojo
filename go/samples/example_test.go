package main

/*
#include <stdlib.h>
*/
import "C"
import "fmt"
import "time"

func Random() int {
	return int(C.random())
}

func Seed(i int) {
	C.srandom(C.uint(i))
}

func main() {
	Seed(int(time.Now().Unix()));

	fmt.Printf("result: %d\n", Random());
}

