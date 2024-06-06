def solve(k):
    pw = 0

    while k - 9 * (pw + 1) * 10**pw > 0:
        k -= 9 * (pw + 1) * 10**pw
        pw += 1

    # numbers here have (pw + 1) digits
    # avoid floating point errors
    delta = k // (pw + 1) + int(k % (pw + 1) > 0)
    number = str(10**pw - 1 + delta)
    k -= (delta - 1) * (pw + 1) + 1

    return number[k]


def main():
    t = int(input())
    for _ in range(t):
        k = int(input())
        print(solve(k))


if __name__ == "__main__":
    main()
