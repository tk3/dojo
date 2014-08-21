package main

import "fmt"
import "net/http"

func HelloHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello!")
}

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "root")
	})

	http.HandleFunc("/hello", HelloHandler)

	http.ListenAndServe(":8080", nil)
}

