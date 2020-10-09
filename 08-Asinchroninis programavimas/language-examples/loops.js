function getFibonacciNumberAtIndex(index) {
    let a = 0;
    let b = 1;
    let currentIndex = 0;
    while(currentIndex < index) {
        [a, b] = [b, a + b];
        currentIndex++;
    }
    return a;
}

const tenthFibonacciNumber = getFibonacciNumberAtIndex(10);
console.log(tenthFibonacciNumber);