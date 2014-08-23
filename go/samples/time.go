package main

import "time"
import "fmt"

func main() {
	now := time.Now()

	fmt.Println(now)
	fmt.Println(now.Format("2006"))
}
