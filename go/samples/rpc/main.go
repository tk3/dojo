package main

import (
	"bytes"
	"encoding/gob"
	"fmt"
	"log"
)

type P struct {
	X, Y, Z int
	Name    string
}

func main() {
	var network bytes.Buffer
	enc := gob.NewEncoder(&network)

	err := enc.Encode(P{3, 4, 5, "Pythagoras"})
	if err != nil {
		log.Fatal("encode error:", err)
	}

	for i, r := range network.Bytes() {
		fmt.Printf("%02x ", r)
		if (i+1)%8 == 0 {
			fmt.Print("\n")
		}
	}
	fmt.Print("\n")
}
