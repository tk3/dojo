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

func TestVersionEqualWorks(t *testing.T) {
	v1 := Version{Major: 1, Minor: 4, Patch: 2}
	v2 := Version{Major: 1, Minor: 4, Patch: 2}
	v3 := Version{Major: 2, Minor: 1, Patch: 0}

	if !(v1 == v2) {
		t.Error("Version Equal test failed.")
	}

	if !(v1 != v3) {
		t.Error("Version Not Equal test failed.")
	}
}
