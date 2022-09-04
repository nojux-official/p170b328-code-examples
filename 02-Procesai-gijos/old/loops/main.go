package main

import "fmt"

func getFibonacciNumberAtIndex(index int) int {
	var a, b = 0, 1
	var currentIndex = 0
	for currentIndex < index {
		a, b = b, a+b
		currentIndex++
	}
	return a
}

func sumOfNumbers(count int) int {
	sum := 0
	for i := 1; i <= count; i++ {
		sum += i
	}
	return sum
}

func main() {
	var tenthFibonacciNumber = getFibonacciNumberAtIndex(10)
	fmt.Println("10th Fibonacci number is", tenthFibonacciNumber)
	var sumOfNumbersUpToTen = sumOfNumbers(10)
	fmt.Println("Sum of numbers up to 10 is", sumOfNumbersUpToTen)
}
