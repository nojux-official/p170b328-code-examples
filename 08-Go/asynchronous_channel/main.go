package main

import (
	"fmt"
	"math/rand"
)

func main() {
	var channel = make(chan int, 5)
	var finishChannel = make(chan bool)
	var names = []string {"First", "Second", "Third", "Fourth", "Fifth"}
	for i := 0; i < 5; i++ {
		var message = rand.Intn(65535)
		go sender(channel, names[i], message)
	}
	go receiver(channel, finishChannel)
	<- finishChannel
}

func sender(channel chan<- int, name string, x int) {
	fmt.Println(name, "is going to send value", x)
	channel <- x
}

func receiver(channel <-chan int, finishChannel chan<- bool) {
	var a int
	for i := 0; i < 5; i++ {
		a = <- channel
		fmt.Println("Received value", a)
	}
	finishChannel <- true
}
