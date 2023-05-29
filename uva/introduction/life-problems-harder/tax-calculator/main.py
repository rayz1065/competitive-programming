from math import ceil

BRACKETS = [
    (180000, 0),
    (300000, 0.1),
    (400000, 0.15),
    (300000, 0.2),
    (10**10, 0.25),
]


def solve(money):
    if money <= BRACKETS[0][0]:
        return 0

    res = 0
    for max_taxed, taxed_fraction in BRACKETS:
        taxed = min(money, max_taxed)
        money -= taxed
        res += taxed * taxed_fraction

    res = max(res, 2000)
    res = ceil(res)
    return res


def main ():
    t = int(input().strip())
    for tc in range(t):
        income = int(input().strip())
        print(f'Case {tc + 1}: {solve(income)}')


if __name__ == '__main__':
    main()
