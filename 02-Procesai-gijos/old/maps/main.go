package main

import (
	"fmt"
	"strings"
)

func wordCount(s string) map[string]int {
	var m = make(map[string]int)
	for _, c := range strings.Fields(s) {
		m[c]++
	}
	return m
}

func main() {
	var counts = wordCount("Hello world sent to a beautiful world")
	fmt.Println(counts)
}
