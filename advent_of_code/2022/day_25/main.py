import itertools

def read_input ():
    lines = []
    try:
        while True:
            line = input()
            lines.append(line)
    except EOFError:
        pass
    return lines

def snafu_to_int (num):
    snafu_map = {
        '2': 2,
        '1': 1,
        '0': 0,
        '-': -1,
        '=': -2
    }
    num = str(num)
    s = 0
    for i, digit in zip(range(len(num)), reversed(num)):
        s += snafu_map[digit] * 5 ** i
    return s

def int_to_snafu (num):
    s = []
    for i in itertools.count():
        s.append(num % 5)
        num //= 5
        if num == 0:
            break
    s.append(0)
    for i, dig in enumerate(s):
        if dig == 3:
            s[i] = '='
            s[i + 1] += 1
        elif dig == 4:
            s[i] = '-'
            s[i + 1] += 1
        elif dig == 5:
            s[i] = 0
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
