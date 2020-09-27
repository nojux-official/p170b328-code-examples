package main

import (
	"fmt"
)

func main() {
	var increaserThreadCount = 10
	var decreaserThreadCount = 9
	var counter = SimpleUnboundedCounter{count: 0}
	var channel = make(chan int)
	for i := 0; i < increaserThreadCount; i++ {
		go increase(channel)
	}
	for i := 0; i < decreaserThreadCount; i++ {
		go decrease(channel)
	}
	var receivedFinishSignals = 0
	for receivedFinishSignals < increaserThreadCount+decreaserThreadCount {
		var message = <-channel
		switch message {
		case 0: // increase value
			counter.Increase()
		case 1: // decrease value
			counter.Decrease()
		case 2: //finish
			receivedFinishSignals++
		}
	}
	fmt.Println(counter.count)
}

func increase(channel chan<- int) {
	for i := 0; i < 50; i++ {
		channel <- 0
	}
	channel <- 2
}

func decrease(channel chan<- int){
	for i := 0; i < 50; i++ {
		channel <- 1
	}
	channel <- 2
}

type SimpleUnboundedCounter struct {
	count int32
}

func (counter *SimpleUnboundedCounter) Increase() {
	counter.count++
}

func (counter *SimpleUnboundedCounter) Decrease() {
	counter.count--
}