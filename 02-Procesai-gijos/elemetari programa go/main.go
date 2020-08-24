package main

import (
	"fmt"
	"sync"
)

func main()  {
	// create names for threads
	var names = [2]string {"First", "Second"}
	// create a wait group that will be used to wait for threads to finish
	var waitGroup = sync.WaitGroup{}
	// we are going to launch 2 threads (call waitGroup.Done() twice), so pass 2 to Add
	waitGroup.Add(len(names))
	for _, name := range names {
		go execute(name, &waitGroup)  // call execute, but launch it in a new thread
	}
	// wait for both threads to finish (until waitGroup.Done is called 2 times)
	waitGroup.Wait()
	fmt.Println("Program finished execution")
}

// Writes some simple output to the console and signals that the main thread may continue by calling .Done()
// name is a string that will be printed. group is a pointer to a wait group we want to wait on. It is important to pass
// a pointer, otherwise a copy of wait group will be passed and .Done() will be called on a copy.
func execute(name string, group *sync.WaitGroup)  {
	defer group.Done()  // defer delays statement execution until the end of function regardless of exceptions
	fmt.Println(name + ": one")
	fmt.Println(name + ": two")
	fmt.Println(name + ": three")
}
