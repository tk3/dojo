package main

import "fmt"
import "sync"

var total int

func func1(n int, wg *sync.WaitGroup) {
	total += n
	wg.Done()
}

func main() {
	var wg sync.WaitGroup

	wg.Add(1)
	go func1(10, &wg)

	wg.Wait()

	fmt.Println(total)
}

