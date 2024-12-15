package main

import (
	"fmt"
	"math"
	"sync"
)

const TerminateMessage = math.MinInt32

// The program demonstrates a consumer-producer pattern with a limited buffer. One thread acts as a producer by adding
// (producing) items to a shared buffer, and one thread acts as a consumer by getting (consuming) items from the shared
// buffer. The buffer is limited in size.
func main() {
	// create a buffer that may contain up to 5 items
	var buffer = initializeBuffer(5)
	// wait group is used for synchronization - its value is set to 2 because we need to wait for two threads to finish
	var waiter = sync.WaitGroup{}
	waiter.Add(2)
	// start the producer. buffer and waiter are passed as references so that Go does not make a copy of them - the
	// buffer is supposed to be shared
	go produce(&buffer, &waiter)
	// an array that will hold our results
	var results = make([]int, 0)
	// consume will update the results array, so pass it as a reference as well
	go consume(&buffer, &results, &waiter)
	// wait for the consumer and the producer to complete
	waiter.Wait()
	// print the results
	for _, item := range results {
		fmt.Println(item)
	}
}

func produce(buffer *LimitedBuffer, waiter *sync.WaitGroup) {
	defer waiter.Done()
	var itemsToProduce = 13
	var startItem = 10
	for i := 0; i < itemsToProduce; i++ {
		var itemToInsert = startItem + i
		buffer.Insert(itemToInsert)
	}
	buffer.Insert(TerminateMessage)
}

func consume(buffer *LimitedBuffer, consumedItems *[]int, waiter *sync.WaitGroup) {
	defer waiter.Done()
	for {
		var item = buffer.Remove()
		if item == TerminateMessage {
			break
		}
		*consumedItems = append(*consumedItems, item)
	}
}

func initializeBuffer(bufferSize int) LimitedBuffer {
	var container = make([]int, bufferSize)
	var mutex = sync.Mutex{}
	var cond = sync.NewCond(&mutex)
	var buffer = LimitedBuffer{container: container, mutex: &mutex, cond: cond}
	return buffer
}

type LimitedBuffer struct {
	container   []int
	from        int
	to          int
	currentSize int
	mutex       *sync.Mutex
	cond        *sync.Cond
}

func (buffer *LimitedBuffer) Insert(item int) {
	buffer.mutex.Lock()
	for buffer.currentSize == len(buffer.container) {
		buffer.cond.Wait()
	}
	buffer.container[buffer.to] = item
	buffer.to = (buffer.to + 1) % len(buffer.container)
	buffer.currentSize++
	buffer.cond.Broadcast()
	buffer.mutex.Unlock()
}

func (buffer *LimitedBuffer) Remove() int {
	buffer.mutex.Lock()
	for buffer.currentSize == 0 {
		buffer.cond.Wait()
	}
	var item = buffer.container[buffer.from]
	buffer.container[buffer.from] = math.MinInt32
	buffer.from = (buffer.from + 1) % len(buffer.container)
	buffer.currentSize--
	buffer.cond.Broadcast()
	buffer.mutex.Unlock()
	return item
}
