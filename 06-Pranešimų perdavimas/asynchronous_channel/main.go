package main

import (
	"fmt"
	"math/rand"
)

// a program that demonstrates asynchronous channel. 5 threads write to the channel and the main thread reads all
// messages from the channel and prints received values
func main() {
	// create channel. It is buffered, so thread will not wait until message is received
	var channel = make(chan int, 5)
	var names = []string {"First", "Second", "Third", "Fourth", "Fifth"}  // one name for each thread
	for _, name := range names {
		var message = rand.Intn(65535)  // generate a random number
		go sender(channel, name, message)  // launch a thread that will send a message back to main thread
	}
	// there must be the same amount of reads and writes to the channel, otherwise the thread will deadlock
	for i := 0; i < len(names); i++ {
		var message = <- channel
		fmt.Println("Received value", message)
	}
}

// a function that writes x to channel and logs what it's doing
func sender(channel chan<- int, name string, x int) {
	fmt.Println(name, "is going to send value", x)
	channel <- x
}
