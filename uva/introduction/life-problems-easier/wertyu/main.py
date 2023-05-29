import sys
from itertools import tee


def pairwise (iterable):
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)


KEYBOARD = [
    '`1234567890-=',
    'QWERTYUIOP[]\\',
    'ASDFGHJKL;\''
    'ZXCVBNM,./'
]
KEY_MAPPING = {
    b: a
    for row in KEYBOARD
    for a, b in pairwise(row)
}


def remap (line):
    return ''.join(KEY_MAPPING.get(x, x) for x in line)


def main ():
    text = sys.stdin.read(-1)
    print(remap(text), end='')


if __name__ == '__main__':
    main()
