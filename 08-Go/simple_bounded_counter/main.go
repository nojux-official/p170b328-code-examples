package main

import (
	"fmt"
	"sync"
)

const min = 0
const max = 50

func main() {
	var mutex = sync.Mutex{}
	var conditionVariable = sync.NewCond(&mutex)
	var counter = SimpleBoundedCounter{count:min, lock:&mutex, cond:conditionVariable}
	var synchronizer = sync.WaitGroup{}
	for i := 0; i < 10; i++ {
		synchronizer.Add(1)
		go func() {
			defer synchronizer.Done()
			for i := 0; i < 50; i++ {
				counter.Increase()
			}
		}()
	}
	for i := 0; i < 9; i++ {
		synchronizer.Add(1)
		go func() {
			defer synchronizer.Done()
			for i := 0; i < 50; i++ {
				counter.Decrease()
			}
		}()
	}
	synchronizer.Wait()
	fmt.Println(counter.count)
}

type SimpleBoundedCounter struct {
	count int32
	lock *sync.Mutex
	cond *sync.Cond
}

func (counter *SimpleBoundedCounter) Increase() {
	counter.lock.Lock()
	for counter.count >= max {
		counter.cond.Wait()
	}
	counter.count++
	counter.cond.Broadcast()
	counter.lock.Unlock()
}

func (counter *SimpleBoundedCounter) Decrease() {
	counter.lock.Lock()
	for counter.count <= min {
		counter.cond.Wait()
	}
	counter.count--
	counter.cond.Broadcast()
	counter.lock.Unlock()
}
