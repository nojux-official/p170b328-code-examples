class Person {
    constructor(firstName, lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    toString() {
        return `${this.firstName} ${this.lastName}`;
    }
}

class Student extends Person {
    constructor(firstName, lastName, grade) {
        super(firstName, lastName);
        this.grade = grade;
    }
}

const students = [
    new Student("Jonas", "Jonaitis", 5),
    new Student("Petras", "Petraitis", 8),
    new Student("Aštrys", "Kirvaitis", 7)
];
const bestStudent = students
    .reduce((best, current) => current.grade > best.grade ? current : best);
console.log(bestStudent.toString());
