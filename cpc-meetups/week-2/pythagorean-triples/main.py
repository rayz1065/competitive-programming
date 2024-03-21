from math import isqrt


def main():
    n = int(input().strip())
    if n <= 2:
        print(-1)
        return

    if n % 4 == 0:
        a = n // 4 * 3
        c = n // 4 * 5
        print(a, c)
        return

    multiplier = 1
    if n % 2 == 0:
        n //= 2
        multiplier *= 2

    c_plus_a = n**2
    c_minus_a = 1

    c = (c_plus_a + c_minus_a) // 2
    a = c_plus_a - c

    a *= multiplier
    c *= multiplier

    print(a, c)


if __name__ == "__main__":
    main()
