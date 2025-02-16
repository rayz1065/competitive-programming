import re


def solve():
    _ = input()
    walruses = input().strip()
    lengths = sorted(map(len, re.findall(r"\.+", walruses)))

    res = 0
    for i, length in enumerate(reversed(lengths)):
        res = max(res, i + 1 + length // 2)

    return len(lengths), res


def main():
    t = int(input().strip())
    for _ in range(t):
        print(" ".join(map(str, solve())))


if __name__ == "__main__":
    main()
