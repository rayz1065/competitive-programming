import re

def part_1(memory):
    return sum(
        int(a) * int(b)
        for a, b
        in re.findall(r'mul\((\d+),(\d+)\)', memory)
    )

def part_2(memory):
    flag = True
    res = 0

    for a, b, do, dont in re.findall(r'mul\((\d+),(\d+)\)|(do)\(\)|(don\'t)\(\)', memory):
        if dont:
            flag = False
        elif do:
            flag = True
        else:
            res += flag * int(a) * int(b)

    return res

def read_input():
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        res.append(line)
    return ''.join(res)

def main():
    memory = read_input()
    print('part1:', part_1(memory))
    print('part2:', part_2(memory))


if __name__ == '__main__':
    main()
