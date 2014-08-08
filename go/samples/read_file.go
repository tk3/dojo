package main

import "os"
import "io/ioutil"
import "fmt"

func main() {
	file, err := os.OpenFile("test.txt", os.O_RDONLY, 0)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	buf, err := ioutil.ReadAll(file)

	fmt.Println(buf)

	file.Close()
}

