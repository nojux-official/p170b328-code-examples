package main

import (
	"fmt"
	"reflect"
)

const MIN = 0
const MAX = 50
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
		// construct the array of three channels [finisherChannel, decreaserChannel, increaserChannel], but some
		//channels may be blocked by setting the corresponding array item to nil. There are three possible scenarios:
		// * [finisherChannel, decreaserChannel, increaserChannel]
		// * [finisherChannel, nil, increaserChannel]
		// * [finisherChannel, decreaserChannel, nil]
		// the goal is to have the same channel at the same index in each iteration, and nil in place of the channel we
		// want to block

		// add finisherChannel
		var activeChannels = []chan int{finisherChannel}
		// if count is more than MIN, add decreaser channel, otherwise add nil
		if counter.count > MIN {
			activeChannels = append(activeChannels, decreaserChannel)
		} else {
			activeChannels = append(activeChannels, nil)
		}
		// if count is less than MAX, add increaser channel, otherwise add nil
		if counter.count < MAX {
			activeChannels = append(activeChannels, increaserChannel)
		} else {
			activeChannels = append(activeChannels, nil)
		}
		// construct an array of case statements of each channel
		var cases []reflect.SelectCase
		for _, c := range activeChannels {
			cases = append(cases, reflect.SelectCase{
				Dir:  reflect.SelectRecv,
				Chan: reflect.ValueOf(c),
			})
		}
		// run select statement, works similarly to a regular select. Returns three values, but we only care about the
		// index of the selected case
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
