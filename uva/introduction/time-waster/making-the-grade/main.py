from math import sqrt
LETTER_GRADES = 'ABCDF'
LETTER_SCORES = {
    'A': 4,
    'B': 3,
    'C': 2,
    'D': 1,
    'F': 0,
}


def normalize_student (line):
    values = [int(x) for x in line.split()]
    absences = values.pop()
    bonus = values.pop()
    return (values, bonus, absences)


def apply_absences (letter, absences):
    curr_idx = LETTER_GRADES.index(letter)
    if absences == 0:
        # gain one grade
        curr_idx -= 1
    else:
        curr_idx += absences // 4

    curr_idx = max(min(curr_idx, len(LETTER_GRADES) - 1), 0)
    return LETTER_GRADES[curr_idx]


def solve ():
    # The requirements are not super clear, this is good enough
    # to get AC but may be entirely adherent to the task
    n_students, n_tests = (int(x) for x in input().strip().split())
    students = [normalize_student(input()) for _ in range(n_students)]
    if n_tests > 2:
        # drop lowest grade
        for values, *_ in students:
            values.remove(min(values))
        n_tests -= 1

    averages = [sum(values) / len(values) for values, *_ in students]
    mean = sum(x for x in averages) / len(students)
    sd = sqrt(sum((x - mean) ** 2 for x in averages) / len(students))
    sd = max(sd, 1)

    cutoff_points = {
        'A': mean + sd,
        'B': mean,
        'C': mean - sd,
        'D': 0
    }

    # adjust averages with bonus points
    averages = [x + (bonus // 2) * 3
                for x, (_, bonus, _) in zip(averages, students)]

    # compute unadjusted marks
    student_marks = [next(letter for letter in LETTER_GRADES
                          if avg >= cutoff_points[letter])
                          for avg in averages]
    # adjust marks with absences
    student_marks = [apply_absences(x, absences)
                     for x, (_, _, absences)
                     in zip(student_marks, students)]

    average_grade_point = sum(LETTER_SCORES[x] for x in student_marks) / len(students)
    return average_grade_point


def main ():
    print('MAKING THE GRADE OUTPUT')
    t = int(input().strip())
    for _ in range(t):
        average_grade_point = solve()
        print(f'{average_grade_point:.1f}')
    print('END OF OUTPUT')


if __name__ == '__main__':
    main()
