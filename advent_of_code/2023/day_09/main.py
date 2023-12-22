from itertools import tee


def pairwise(it):
    a, b = tee(it)
    next(b)
    return zip(a, b)


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield [int(x) for x in line.split()]


def pairwise_subtract(sequence):
    return [b - a for a, b in pairwise(sequence)]


def find_next(sequence):
    if len(sequence) == 1:
        return 0

    next_ = find_next(pairwise_subtract(sequence))
    return sequence[-1] + next_


def find_prev(sequence):
    if len(sequence) == 1:
        return 0

    prev_ = find_prev(pairwise_subtract(sequence))
    return sequence[0] - prev_


def part_1(sequences):
    return sum(find_next(x) for x in sequences)


def part_2(sequences):
    return sum(find_prev(x) for x in sequences)


def main():
    sequences = list(read_lines())
    print("part_1:", part_1(sequences))
    print("part_2:", part_2(sequences))


if __name__ == "__main__":
    main()
