student_grades = {
    "Jonas": 4,
    "Petras": 9,
    "Antanas": 8
}

for name, grade in student_grades.items():
    print("Student", name, "got grade", grade)

highest_grade = max(student_grades.values())
print(highest_grade)
student_names = sorted(student_grades.keys())
for name in student_names:
    print(name)
