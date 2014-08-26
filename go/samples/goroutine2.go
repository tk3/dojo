package main

import "fmt"
import "sync"
import "runtime"

var total int

func func1(n int, wg *sync.WaitGroup) {
	total += n
	wg.Done()
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	var wg sync.WaitGroup

	for i := 0; i < 100; i++ {
		wg.Add(1)
		go func1(10, &wg)
	}
	wg.Wait()

	fmt.Println(total)
}

