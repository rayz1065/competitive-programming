from itertools import tee


def min_max(it):
    a, b = tee(it)
    return min(a), max(b)


def tc():
    n, _ = map(int, input().strip().split())

    ones = set()

    for r in range(n):
        row = input().strip()
        for c, cell in enumerate(row):
            if cell == "1":
                ones.add((r, c))

    if not ones:
        return 0

    r_min, r_max = min_max(x[0] for x in ones)
    c_min, c_max = min_max(x[1] for x in ones)

    return len(ones) == (c_max - c_min + 1) * (r_max - r_min + 1)


def main():
    t = int(input().strip())
    for _ in range(t):
        print(int(tc()))


if __name__ == "__main__":
    main()
