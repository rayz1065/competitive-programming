MOD = 10**9 + 7


def jacobsthal(n):
    return ((pow(2, n, MOD) - pow(-1, n, MOD)) * pow(3, -1, MOD)) % MOD


def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        res = (jacobsthal(n - 1) * 2) % MOD
        print(res)


if __name__ == "__main__":
    main()
