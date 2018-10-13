package main

import "fmt"

func main() {
	a := [5]float64{ 98, 93, 77, 82, 83 }
	var sum float64 = 0
	for _, value := range a {
		sum += value
	}
	fmt.Println(sum / float64(len(a)))
}
