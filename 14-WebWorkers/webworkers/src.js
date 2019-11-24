(() => {
    function writeResult(sum) {
        const container = document.getElementById("result");
        container.innerText = sum;
    }

    function generateRandomNumbers(size) {
        const numbers = [];
        for (let i = 0; i < size; i++) {
            const number = Math.floor(Math.random() * 1000);
            numbers.push(number);
        }
        return numbers;
    }

    function getSumAsync(numbers) {
        return new Promise(resolve => {
            const threadCount = 8;
            const chunkSize = numbers.length / threadCount;
            const partialSums = [];
            for (let i = 0; i < threadCount; i++) {
                const chunkStart = i * chunkSize;
                const chunkEnd = (i + 1) * chunkSize;
                const worker = new Worker("worker.js");
                worker.onmessage = event => {
                    partialSums.push(event.data);
                    if (partialSums.length === threadCount) {
                        resolve(partialSums);
                    }
                };
                worker.postMessage(numbers.slice(chunkStart, chunkEnd));
            }
        });
    }

    document.addEventListener("DOMContentLoaded", async () => {
        const numbers = generateRandomNumbers(10000);
        const partialSums = await getSumAsync(numbers);
        writeResult(partialSums.reduce((acc, num) => acc + num));
    });
})();
