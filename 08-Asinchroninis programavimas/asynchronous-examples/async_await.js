/**
 * a program that demonstrates how to use async functions
 */

/**
 * Returns an array of numbers from 0 to count
 * @returns {Promise<number[]>}
**/
async function generateNumbers(count) {
    return [...Array(count).keys()];
}

/**
 * A function that calculates sum of all squares of numbers from 0 to 10M and logs it to console
 * @returns {Promise<void>}
 */
async function getSquaredAsync() {
    try {
        // await here stops execution of this function, sets generateNumbers to run in event loop and and the remainder
        // of this function to run in event loop after generateNumbers will have been finished
        const numbers = await generateNumbers(10000000);
        const squaredSum = numbers
            .map(num => num * num)
            .reduce((acc, num) => acc + num);
        console.log(squaredSum);
    } catch (e) {
        console.error(e);
    }
}

getSquaredAsync().then(()  => {
    console.log("Finished");  // this will be printed after printing squared sum
});
console.log("Calculating");  // this will be printed earlier than squared sum
