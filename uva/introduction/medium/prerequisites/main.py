while True:
    line = input().strip()
    if line == '0':
        break
    n_courses, n_categories = (int(x) for x in line.split())

    courses = set()
    while len(courses) < n_courses:
        courses.update(input().strip().split())

    categories = []
    for _ in range(n_categories):
        _, min_followed, *cat_courses = input().strip().split()
        min_followed = int(min_followed)
        categories.append((min_followed, cat_courses))

    for min_followed, cat_courses in categories:
        followed = len(courses.intersection(cat_courses))
        if followed < min_followed:
            print('no')
            break
    else:
        print('yes')
