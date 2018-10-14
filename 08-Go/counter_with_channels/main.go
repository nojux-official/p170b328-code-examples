package main

import (
	"fmt"
	"sync"
)

func main() {
	var synchronizer = sync.WaitGroup{}
	var counter = SimpleUnboundedCounter{count: 0}
	var channel = make(chan int)
	go func() {
		for {
			var message = <- channel
			switch message {
			case 0: // increase value
				counter.Increase()
			case 1: // decrease value
				counter.Decrease()
			case 2: //finish
				break
			}
		}
	}()
	for i := 0; i < 10; i++ {
		synchronizer.Add(1)
		go func() {
			defer synchronizer.Done()
			for i := 0; i < 50; i++ {
				channel <- 0
			}
		}()
	}
	for i := 0; i < 9; i++ {
		synchronizer.Add(1)
		go func() {
			defer synchronizer.Done()
			for i := 0; i < 50; i++ {
				channel <- 1
			}
		}()
	}
	synchronizer.Wait()
	channel <- 2
	fmt.Println(counter.count)
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