def main():
    n = int(input().strip())
    values = [int(x) for x in input().strip().split()]
    frequencies = {}
    for value in values:
        frequencies.setdefault(value, 0)
        frequencies[value] += 1

    majority_size = max(frequencies.values())
    if majority_size > (n + 1) // 2:
        print("NO")
    else:
        print("YES")


if __name__ == "__main__":
    main()
