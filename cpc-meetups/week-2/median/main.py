def main():
    n, median = map(int, input().strip().split())
    values = list(map(int, input().strip().split()))
    smaller = sum(x < median for x in values)
    equal = sum(x == median for x in values)
    
    # index of the first element is `smaller`
    # index of the last element is `smaller + equal - 1`
    # index of the median is (n - 1) // 2

    res = 0
    while not (smaller <= (n - 1) // 2 <= smaller + equal - 1):
        res += 1
        equal += 1
        n += 1

    print(res)


if __name__ == "__main__":
    main()
