package main

import (
	"fmt"
	"math"
	"sync"
)

const TerminateMessage = math.MinInt32

func main() {
	var buffer = initializeBuffer(5)
	var waiter = sync.WaitGroup{}
	waiter.Add(2)
	go produce(&buffer, &waiter)
	var results = make([]int, 0)
	go consume(&buffer, &results, &waiter)
	waiter.Wait()
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
	buffer.container[buffer.currentSize] = item
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
