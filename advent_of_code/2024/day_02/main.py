from itertools import tee


def pairwise(it):
    a, b = tee(it)
    next(b, None)
    return zip(a, b)


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield list(map(int, line.strip().split()))


def read_input():
    return list(read_lines())


def is_safe(report):
    return all(1 <= abs(a - b) <= 3 for a, b in pairwise(report)) and (
        all(a < b for a, b in pairwise(report))
        or all(a > b for a, b in pairwise(report))
    )


def is_almost_safe(report):
    return is_safe(report) or any(
        is_safe(report[0:i] + report[i + 1 :]) for i, _ in enumerate(report)
    )


def part_2(reports):
    return sum(map(is_almost_safe, reports))


def part_1(reports):
    return sum(map(is_safe, reports))


def main():
    reports = read_input()
    print("part1:", part_1(reports))
    print("part2:", part_2(reports))


if __name__ == "__main__":
    main()
