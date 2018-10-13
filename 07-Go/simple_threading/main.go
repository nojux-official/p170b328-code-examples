package main

import (
	"fmt"
	"sync"
)

func main() {
	var waitGroup sync.WaitGroup
	for i := 0; i < 10; i++ {
		waitGroup.Add(1)
		go process(i, &waitGroup)
	}
	waitGroup.Wait()
	fmt.Println("Programa baigė darbą.")
}

func process(k int, waitGroup *sync.WaitGroup) {
	defer waitGroup.Done()
	fmt.Printf("Procesas nr.: %d\n", k)
}
