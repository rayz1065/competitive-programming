import re
from itertools import accumulate


def is_valid (isbn):
    isbn = isbn.replace('-', '').replace(' ', '')
    if re.match(r'^\d{9}[\dX]$', isbn) is None:
        return False

    values = list(isbn)
    if values[-1] == 'X':
        values[-1] = '10'
    values = [int(x) for x in values]

    partial_sums = accumulate(values)
    return sum(partial_sums) % 11 == 0


def main ():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        valid = is_valid(line)
        status = 'correct' if valid else 'incorrect'
        print(f'{line} is {status}.')


if __name__ == '__main__':
    main()
