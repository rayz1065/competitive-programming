from math import isqrt


def reach_next_level(level, m):
    k = level
    # m = m' * k
    m_prime = m // k
    # m + t * k = k(m' + t)
    # m' + t = k * (k + 1) ** 2 * x ** 2
    # t = k * (k + 1) ** 2 * x ** 2 - m' >= 0

    x = 0
    while k * (k + 1) ** 2 * x**2 - m_prime < 0:
        x += 1

    t = k * (k + 1) ** 2 * x**2 - m_prime
    m += t * k

    assert isqrt(m) ** 2 == m
    m = isqrt(m)

    return t, m


def main():
    n = int(input().strip())

    m = 2
    level = 1
    while level <= n:
        moves, m = reach_next_level(level, m)
        print(moves)
        level += 1
        assert m % level == 0


if __name__ == "__main__":
    main()
