package main

import "fmt"

func main() {
	var channel = make(chan int)
	go generateNumbers(channel)
	var total = 0
	// loop over the channel - the loop breaks when the channel is closed
	for number := range channel {
		total += number
	}
	fmt.Println(total)
}

func generateNumbers(output chan<- int) {
	for i := 0; i <= 100; i++ {
		output <- i
	}
	close(output)
}
