def find_value (x):
    x = x.lower()
    s = 0
    for char in x:
        if 'a' <= char <= 'z':
            s += ord(char) - ord('a') + 1
    return s

def to_one_digit (x):
    if x == 0:
        return x
    x = x % 9
    if x == 0:
        return 9
    return x

try:
    while True:
        a, b = input(), input()
        a, b = find_value(a), find_value(b)
        a, b = to_one_digit(a), to_one_digit(b)
        a, b = min(a, b), max(a, b)
        ratio = round((a/b) * 100, 2)
        print('{:.2f}'.format(ratio), '%')
except EOFError:
    pass
