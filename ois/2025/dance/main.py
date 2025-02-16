def main():
    input()
    d = int(input().strip())
    a = list(int(x) for x in input().strip().split())
    b = list(int(x) for x in input().strip().split())
    print("YES" if all(y - x <= d for x, y in zip(a, b)) else "NO")


if __name__ == "__main__":
    main()
