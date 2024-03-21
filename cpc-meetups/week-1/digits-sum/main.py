from functools import cache


def sum_digits(n):
    return sum(int(x) for x in str(n))


def solve(a, b):
    frequency = 0
    res = 0

    while a % 10 != 0 and a <= b:
        res += sum_digits(a)
        frequency += 1
        a += 1

    while b % 10 != 9 and a <= b:
        res += sum_digits(b)
        frequency += 1
        b -= 1

    if a > b:
        return frequency, res

    a //= 10
    b //= 10
    other_frequency, other_res = solve(a, b)

    res += other_res * 10 + (b - a + 1) * 45
    frequency += other_frequency * 10

    return frequency, res


@cache
def _dp_solve(b, digits, k_sum, all_digits_equal):
    """
    Returns the number of integers with `digits` digits and digit sum equal to `k_sum`
    such that the produced number is at most b.
    """
    if digits == 0:
        return k_sum == 0

    res = 0
    b_digit = int(b[len(b) - digits])
    for next_digit in range(min(10, k_sum + 1)):
        if all_digits_equal and next_digit > b_digit:
            continue

        res += _dp_solve(
            b,
            digits - 1,
            k_sum - next_digit,
            all_digits_equal and next_digit == b_digit,
        )

    return res


def dp_solve(b):
    if b < 0:
        return 0

    b = str(b)
    digits = len(b)
    res = 0
    for k in range(digits * 9 + 1):
        res += _dp_solve(b, digits, k, True) * k

    return res


def main():
    t = int(input().strip())
    for _ in range(t):
        a, b = (int(x) for x in input().strip().split())
        print(dp_solve(b) - dp_solve(a - 1))


if __name__ == "__main__":
    main()
