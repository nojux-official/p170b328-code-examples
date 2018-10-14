package main

import (
	"fmt"
	"sync"
)

func main() {
	var synchronizer = sync.WaitGroup{}
	var counter = SimpleUnboundedCounter{count: 0}
	var increaserChannel = make(chan int)
	var decreaserChannel = make(chan int)
	var finisherChannel = make(chan int)
	go func() {
		for {
			select {
				case <- increaserChannel:
					counter.Increase()
				case <- decreaserChannel:
					counter.Decrease()
				case <- finisherChannel:
					break
			}
		}
	}()
	for i := 0; i < 10; i++ {
		synchronizer.Add(1)
		go func() {
			defer synchronizer.Done()
			for i := 0; i < 50; i++ {
				increaserChannel <- 0
			}
		}()
	}
	for i := 0; i < 9; i++ {
		synchronizer.Add(1)
		go func() {
			defer synchronizer.Done()
			for i := 0; i < 50; i++ {
				decreaserChannel <- 0
			}
		}()
	}
	synchronizer.Wait()
	finisherChannel <- 2
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