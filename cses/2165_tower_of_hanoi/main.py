def anoi(n, a, b, free):
    if n == 1:
        print(a, b)
        return

    anoi(n - 1, a, free, b)
    anoi(1, a, b, free)
    anoi(n - 1, free, b, a)


def main():
    n = int(input().strip())
    print(2**n - 1)
    anoi(n, 1, 3, 2)


if __name__ == "__main__":
    main()
