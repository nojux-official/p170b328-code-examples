class Person:
    def __init__(self, first_name, last_name):
        self.first_name = first_name
        self.last_name = last_name

    def __str__(self):
        return "%(first_name)s %(last_name)s" % {
            "first_name": self.first_name,
            "last_name": self.last_name
        }


class Student(Person):
    def __init__(self, first_name, last_name, grade):
        super().__init__(first_name, last_name)
        self.grade = grade


students = [Student("Jonas", "Jonaitis", 5),
            Student("Petras", "Petraitis", 8),
            Student(last_name="Kirvaitis", first_name="Aštrys",
                    grade=7)]

best_student = max(students, key=lambda student: student.grade)
print(best_student)
