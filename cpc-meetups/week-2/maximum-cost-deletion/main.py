def minimize_operations(chars):
    swaps = 0
    last_char = chars[0]
    for char in chars[1:]:
        if char != last_char:
            swaps += 1
            last_char = char

    return swaps // 2 + swaps % 2 + 1


def main():
    t = int(input().strip())
    for _ in range(t):
        n, a, b = map(int, input().strip().split())
        chars = input().strip()

        # remove each character individually
        res = n * b

        # minimize the number of operations
        res = max(res, b * minimize_operations(chars))

        res += n * a

        print(res)


if __name__ == "__main__":
    main()
