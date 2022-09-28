from itertools import tee

def pairwise(iterable):
    a, b = tee(iterable)
    next(b)
    return zip(a, b)

def solve():
    key_lines = [
        'qwertyuiop',
        'asdfghjkl',
        'zxcvbnm'
    ]
    key_mappings = {}
    for line in key_lines:
        for a, b in pairwise(line):
            key_mappings[a] = b
    input()
    line = input()
    return ''.join(key_mappings[x] for x in line)

if __name__ == '__main__':
    print(solve())
