package main

import (
	"fmt"
	"reflect"
	"sync"
)

const min = 0
const max = 50

func main() {
	var synchronizer = sync.WaitGroup{}
	var counter = SimpleUnboundedCounter{count: 0}
	var increaserChannel = make(chan int)
	var decreaserChannel = make(chan int)
	var finisherChannel = make(chan int)
	go func() {
		for {
			var activeChannels = []chan int {finisherChannel}
			if counter.count > min {
				activeChannels = append(activeChannels, decreaserChannel)
			} else {
				activeChannels = append(activeChannels, nil)
			}
			if counter.count < max {
				activeChannels = append(activeChannels, increaserChannel)
			} else {
				activeChannels = append(activeChannels, nil)
			}
			var cases []reflect.SelectCase
			for _, c := range activeChannels {
				cases = append(cases, reflect.SelectCase{
					Dir: reflect.SelectRecv,
					Chan: reflect.ValueOf(c),
				})
			}
			chosenIndex, _, _ := reflect.Select(cases)
			switch chosenIndex {
			case 0:
				break
			case 1:
				counter.Decrease()
			case 2:
				counter.Increase()
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

