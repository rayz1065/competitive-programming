from math import log2, ceil, sqrt
from random import randint, choices, choice


def main():
    n = 300000
    k = randint(1, ceil(sqrt(n)))

    print(n, k)
    for i in range(2, n + 1):
        print(i, randint(1, i - 1))

    nodes = list(range(1, n + 1))
    shops = choices(nodes, k=k)
    print(" ".join(str(x) for x in shops))

    for _ in range(n):
        print(choice(shops), randint(0, ceil(log2(n))))


if __name__ == "__main__":
    main()
