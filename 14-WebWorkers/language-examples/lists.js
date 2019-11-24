const a = [98, 93, 77, 82, 83];
let aSum = 0;
for (value of a) {
    aSum += value;
}
console.log(aSum);
// alternative
const aSum2 = a.reduce((acc, num) => acc + num);
console.log(aSum2);