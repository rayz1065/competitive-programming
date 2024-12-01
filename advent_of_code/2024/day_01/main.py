def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield [int(x) for x in line.split()]


def read_input():
    list_1, list_2 = [], []

    for a, b in read_lines():
        list_1.append(a)
        list_2.append(b)

    return list_1, list_2


def part_1(list_1, list_2):
    return sum(abs(a - b) for a, b in zip(sorted(list_1), sorted(list_2)))


def part_2(list_1, list_2):
    frequencies = {}

    for b in list_2:
        frequencies.setdefault(b, 0)
        frequencies[b] += 1

    return sum(a * frequencies.get(a, 0) for a in list_1)


def main():
    list_1, list_2 = read_input()

    print("part1:", part_1(list_1, list_2))
    print("part2:", part_2(list_1, list_2))


if __name__ == "__main__":
    main()
