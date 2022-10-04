package main

import (
	"fmt"
	"reflect"
)

const min = 0
const max = 50
const increaserCount = 10
const decreaserCount = 9

func main() {
	var counter = SimpleBoundedCounter{count: 0}
	var increaserChannel = make(chan int)
	var decreaserChannel = make(chan int)
	var finisherChannel = make(chan int)
	for i := 0; i < increaserCount; i++ {
		go func() {
			for i := 0; i < 50; i++ {
				increaserChannel <- 0
			}
			finisherChannel <- 2
		}()
	}
	for i := 0; i < decreaserCount; i++ {
		go func() {
			for i := 0; i < 50; i++ {
				decreaserChannel <- 0
			}
			finisherChannel <- 2
		}()
	}
	var remainingThreads = decreaserCount + increaserCount
	for remainingThreads != 0 {
		var activeChannels = []chan int{finisherChannel}
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
				Dir:  reflect.SelectRecv,
				Chan: reflect.ValueOf(c),
			})
		}
		chosenIndex, _, _ := reflect.Select(cases)
		switch chosenIndex {
		case 0:
			remainingThreads--
		case 1:
			counter.Decrease()
		case 2:
			counter.Increase()
		}
	}
	fmt.Println(counter.count)
}

type SimpleBoundedCounter struct {
	count int32
}

func (counter *SimpleBoundedCounter) Increase() {
	counter.count++
}

func (counter *SimpleBoundedCounter) Decrease() {
	counter.count--
}
