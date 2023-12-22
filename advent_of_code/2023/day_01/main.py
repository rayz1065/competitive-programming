import re


def get_lines():
    try:
        while True:
            line = input().strip()
            if line == "":
                break
            yield line
    except EOFError:
        pass


def part_1(lines):
    total = 0
    for line in lines:
        res = re.findall(r"\d", line)
        total += int(res[0] + res[-1])

    return total


def part_2(lines):
    NUMBERS = {
        "one": 1,
        "two": 2,
        "three": 3,
        "four": 4,
        "five": 5,
        "six": 6,
        "seven": 7,
        "eight": 8,
        "nine": 9,
    }
    for i in range(10):
        NUMBERS[str(i)] = i

    # part 2
    total = 0
    for line in lines:
        res = re.findall("|".join(NUMBERS.keys()), line)
        total += NUMBERS[res[0]] * 10 + NUMBERS[res[-1]]

    return total


def main():
    lines = list(get_lines())

    print("part1:", part_1(lines))
    print("part2:", part_2(lines))


if __name__ == "__main__":
    main()
