package main

import (
	"testing"
)

func TestVersionInitializeWorks(t *testing.T) {
	v := Version{Major: 1, Minor: 4, Patch: 2}
	if !(v.Major == 1 && v.Minor == 4 && v.Patch == 2) {
		t.Error("Version initialize test failed.")
	}
}

func TestVersionStringWorks(t *testing.T) {
	v := Version{Major: 1, Minor: 4, Patch: 2}
	if !(v.ToString() == "1.4.2") {
		t.Error("Version ToString() test failed.")
	}
}
