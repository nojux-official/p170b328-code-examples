function doHeavyComputation(callback){
    setTimeout(() => {
        const numbers = [...Array(100000).keys()];
        const squaredSum = numbers
            .map(num => num * num)
            .reduce((acc, num) => acc + num);
        callback(squaredSum);
    }, 1000);
}

doHeavyComputation(squaredSum => {
    console.log(`Squared sum is ${squaredSum}`);
});
