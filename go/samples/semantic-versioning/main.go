package main

import "fmt"

type Version struct {
	Major int
	Minor int
	Patch int
}

func (v *Version) ToString() {
	fmt.Sprintf("%d.%d.%d", v.Major, v.Minor, v.Patch)
}

func main() {
	fmt.Println("vim-go")
}
