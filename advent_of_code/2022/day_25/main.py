from sys import stdin
import itertools

SNAFU_MAP = {
    '2': 2,
    '1': 1,
    '0': 0,
    '-': -1,
    '=': -2
}

def read_input ():
    return [x.strip() for x in stdin.readlines()]

def snafu_to_int (num):
    return sum(SNAFU_MAP[digit] * 5 ** i for i, digit in enumerate(reversed(num)))

def int_to_snafu (num):
    s = []
    for i in itertools.count():
        s.append(num % 5)
        num //= 5
        if num == 0:
            break
    s.append(0)
    dig_map = {
        3: '=',
        4: '-',
        5: '0'
    }
    for i, dig in enumerate(s):
        if dig >= 3:
            s[i] = dig_map[dig]
            s[i + 1] += 1
    if s[-1] == 0:
        s.pop()
    return ''.join(str(x) for x in reversed(s))

def main ():
    nums = read_input()
    tot = sum(snafu_to_int(num) for num in nums)
    snafu_tot = int_to_snafu(tot)
    assert tot == snafu_to_int(snafu_tot)
    print('part_1:', snafu_tot)

if __name__ == '__main__':
    main()
