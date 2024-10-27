package main

import (
	"fmt"
	"math"
)

const intEndMessage = math.MaxInt32
const floatEndMessage = math.MaxFloat64

// the program has main + two extra threads. One thread generates integer values and sends them via integer channel,
// second thread does the same with float values. Main receives messages from both threads and computes integer and
// float sums of received values
func main() {
	// create channels that will be used to send messages
	var intChannel = make(chan int)
	var floatChannel = make(chan float64)
	// spawn the threads
	go generateIntegers(intChannel)
	go generateFloats(floatChannel)
	// at the end both threads will send end-of-work messages. Count how many such messages are received
	var finishedThreads = 0
	// variables for sum - the result of this program
	var intSum = 0
	var floatSum = 0.0
	for finishedThreads != 2 {
		// select statements receives from one of the channels, whichever is ready first
		select {
		case intValue := <-intChannel:
			if intValue != intEndMessage {
				// not end of work, compute sum
				intSum += intValue
			} else {
				// end of work
				finishedThreads++
			}
		case floatValue := <-floatChannel:
			if floatValue != floatEndMessage {
				// not end of work, compute sum
				floatSum += floatValue
			} else {
				// end of work
				finishedThreads++
			}
		}
	}
	// output results
	fmt.Println("Integer sum:", intSum)
	fmt.Println("Float sum:", floatSum)
}

// writes all numbers from 0 to 15 into the channel, followed by termination message
func generateIntegers(outChannel chan<- int) {
	for i := 0; i < 15; i++ {
		outChannel <- i
	}
	outChannel <- intEndMessage
}

// writes numbers from 0.5 to 19.5 with a step of 1 into the channel, followed by termination message
func generateFloats(outChannel chan<- float64) {
	for i := 0.5; i < 20; i += 1 {
		outChannel <- i
	}
	outChannel <- floatEndMessage
}
