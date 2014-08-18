package main

import "fmt"

func main() {
	m := map[string]string {
		"key01": "val01",
		"key02": "val02",
	}

	fmt.Println(m)

	v1 := m["key01"]
	fmt.Println(v1)

	_, is_exists := m["key_99"]
	fmt.Println("exists: ", is_exists)


	m["key03"] = "val03"
	m["key04"] = "val04"
	fmt.Println(m)

	m["key03"] = "val03"

	delete(m, "key02")
	fmt.Println(m)
}

