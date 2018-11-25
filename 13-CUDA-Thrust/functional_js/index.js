#!/usr/bin/env node

function getVector() {
    return [...Array(20).keys()].map(i => i + 1);
}

function main() {
    const vector = getVector();
    const sum = vector
        .filter(i => i % 2 === 0) // filter only even
        .map(i => i * i) // map to squares
        .reduce((acc, i) => acc + i, 0); // reduce to sum
    console.log(sum)
}

main();
