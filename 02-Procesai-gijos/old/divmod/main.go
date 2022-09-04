package main

import (
	"fmt"
)

func divmod(x, y int) (divResult, modResult int) {
	divResult = x / y
	modResult = x % y
	return
}

func main() {
	div, mod := divmod(15, 7)
	fmt.Println("div operacijos rezultatas", div)
	fmt.Println("mod operacijos rezultatas", mod)
}
