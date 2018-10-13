package main

import "fmt"

func printNumbersBackwards() {
	for i := 0; i < 20; i++ {
		defer fmt.Println(i)
	}
}

func main() {
	printNumbersBackwards()
}
