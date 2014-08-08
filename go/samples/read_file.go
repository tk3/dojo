package main

import "os"
import "fmt"

func main() {
	file, err := os.OpenFile("test.txt", os.O_RDONLY, 0)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	file.Close()
}

