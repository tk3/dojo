package main

import "fmt"
import "net/http"

func HelloHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello!")
}

func main() {
	echoHandler := func(w http.ResponseWriter, r *http.Request) {
		for name, values := range r.Header {
			fmt.Fprintf(w, "%s:\n", name)
			for _, value := range values {
				fmt.Fprintf(w, "  [%s]\n", value)
			}
			fmt.Fprintln(w, "")
		}
	}

	queryHandler := func(w http.ResponseWriter, r *http.Request) {
		for name, value := range r.URL.Query() {
			fmt.Fprintf(w, "%s=%s\n", name, value)
		}
	}

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "root")
	})

	http.HandleFunc("/hello", HelloHandler)

	http.HandleFunc("/echo", echoHandler)

	http.HandleFunc("/query", queryHandler)

	http.ListenAndServe(":8080", nil)
}

