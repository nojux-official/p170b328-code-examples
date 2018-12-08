const generateNumbers = new Promise(resolve => {
    setTimeout(() => {
        resolve([...Array(100000).keys()]);
    }, 1000);
});

generateNumbers.then(numbers => {
    return numbers
        .map(num => num * num)
        .reduce((acc, num) => acc + num);
}).then(squaredSum => {
    console.log(squaredSum);
}).catch(err => {
    console.log(err);
});
