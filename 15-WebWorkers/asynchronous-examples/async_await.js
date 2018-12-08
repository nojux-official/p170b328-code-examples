const generateNumbers = new Promise(resolve => {
    setTimeout(() => {
        resolve([...Array(100000).keys()]);
    }, 1000);
});

async function getSquaredAsync() {
    try {
        const numbers = await generateNumbers;
        const squaredSum = numbers
            .map(num => num * num)
            .reduce((acc, num) => acc + num);
        console.log(squaredSum);
    } catch (e) {
        console.error(e);
    }
}

getSquaredAsync();
