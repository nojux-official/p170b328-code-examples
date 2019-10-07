package main

import "fmt"

// a program that demonstrates how to exchange messages between threads
func main() {
	// Communication between threads is done using a channel without buffer - both threads will be blocked until message
	// sent. Sender thread is launched, sender writes a message and main thread receives and prints it.
	var channel = make(chan int)  // a channel for communication
	go func() {
		channel <- 10 // write value to the channel; this will wait until someone reads the value from the channel
	}()
	var x = <- channel  // this will wait until someone writes to this channel and then read the value
	fmt.Println("Received value", x)
}
