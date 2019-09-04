package main

import (
	"fmt"
	"math"
	"runtime"
)

func getCurrentOS() string {
	switch os := runtime.GOOS; os {
	case "darwin":
		return "OS X"
	case "linux":
		return "Linux"
	default:
		return "Unknown OS"
	}
}

func powerWithLowerLimit(x, n, limit float64) float64 {
	if value := math.Pow(x, n); value < limit {
		return limit
	} else {
		return value
	}
}

func main() {
	os := getCurrentOS()
	fmt.Println("Current OS is", os)
	fmt.Println(
		powerWithLowerLimit(3, 2, 5),
		powerWithLowerLimit(3, 2, 20),
	)
}
