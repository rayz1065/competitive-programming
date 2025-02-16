def main():
    n, m = (int(x) for x in input().strip().split())

    if n > m:
        print(-1)
        return

    for i in range(n):
        print("#" * i + "." * (m - i))


if __name__ == "__main__":
    main()
