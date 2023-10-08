package main

import (
	"fmt"
)

const INCREASE = 0
const DECREASE = 1
const FINISHED = 2

// the program spawns two types of threads - some of them send messages to increase the value of the counter, others -
// to decrease the value. The count is managed by main - main is the receiver of the messages, other threads are the senders
func main() {
	// the amounts of threads
	var increaserThreadCount = 10
	var decreaserThreadCount = 9
	// the count that will be managed by main
	var count = 0
	// create a channel to exchange messages
	var channel = make(chan int)
	// start goroutines
	for i := 0; i < increaserThreadCount; i++ {
		go increase(channel)
	}
	for i := 0; i < decreaserThreadCount; i++ {
		go decrease(channel)
	}
	// the threads can send three types of messages - to increase the value, to decrease the value or an end-of-work
	// signal. When the amount of received end-of-work signals is equal to the amount of spawned threads, stop receiving
	// messages
	var receivedFinishSignals = 0
	for receivedFinishSignals < increaserThreadCount+decreaserThreadCount {
		// get the message and do the required operation based on the message value
		var message = <-channel
		switch message {
		case INCREASE: // increase value
			count++
		case DECREASE: // decrease value
			count--
		case FINISHED: //finish
			receivedFinishSignals++
		}
	}
	// print the final result
	fmt.Println(count)
}

// increase - send 50 messages INCREASE to the channel
func increase(channel chan<- int) {
	for i := 0; i < 50; i++ {
		channel <- INCREASE
	}
	channel <- FINISHED
}

// decrease - send 50 messages DECREASE to the channel
func decrease(channel chan<- int) {
	for i := 0; i < 50; i++ {
		channel <- DECREASE
	}
	channel <- FINISHED
}
