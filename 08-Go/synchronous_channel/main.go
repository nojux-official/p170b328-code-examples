package main

import "fmt"

func main() {
	var channel = make(chan int)
	var finishChannel = make(chan bool)
	go sender(channel)
	go receiver(channel, finishChannel)
	<-finishChannel
}

func sender(channel chan<- int) {
	var x = 10
	channel <- x
}

func receiver(channel <-chan int, finishChannel chan<- bool) {
	var x = <- channel
	fmt.Println("Received value", x)
	finishChannel <- true
}