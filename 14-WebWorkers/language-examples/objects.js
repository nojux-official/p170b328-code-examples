const students = [
    {name: "Jonas", grade: 4},
    {name: "Petras", grade: 9},
    {name: "Antanas", grade: 8}
];
students
    .forEach(student =>
        console.log("Student", student.name, "got grade", student.grade)
    );
const grades = students
    .map(student => student.grade)
const highestGrade = Math.max(...grades);
console.log(highestGrade);
const studentNames = students.map(student => student.name);
studentNames
    .forEach(name => console.log(name));
