def main():
    t = int(input())

    for _ in range(t):
        n, k = (int(x) for x in input().strip().split())
        if k == 1 or n in (k * (k + 1) // 2, k * (k + 1) // 2 + 1):
            print("YES")
        else:
            print("NO")


if __name__ == "__main__":
    main()
